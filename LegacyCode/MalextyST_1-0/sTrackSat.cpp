// C++ Imports
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <Serial/include/serial.h>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"
#include "json.hpp"

// SGP4 Imports
#include <SGP4/CoordTopocentric.h>
#include <SGP4/CoordGeodetic.h>
#include <SGP4/Observer.h>
#include <SGP4/Util.h>
#include <SGP4/SGP4.h>

// Program Parts Imports
#include "sTrackSat.hpp"
#include "sConfigHandler.hpp"

// Setup
using json = nlohmann::json;

// Variables
#define MICROSECOND 1000000
int msgCount = 0;
std::string serPort;
std::string serBaud;

// Variables to track Satellite
std::string TLE_Name;
std::string TLE_LineA;
std::string TLE_LineB;
std::string TLE_Table;
float observerLatitude;
float observerLongitude;
// TODO Add Observer Elevation

// Variables to hold current Satellite position
float currSat_Azimuth;
float currSat_Elevation;
float currSat_Range;
float currSat_RangeRate;
float currSat_Latitude;
float currSat_Longitude;
float currSat_Altitude;
bool currSat_AOSStat;

// Function to take a float, and return it as a string limited to 2 decimal places
std::string floatToStr(float inFloat)
{
    std::stringstream strStream;
    strStream << std::fixed;
    strStream.precision(2); // Limit to 2 decimal places
    strStream << inFloat;
    return strStream.str();
}

// sTrackSat - Entry Point
void sTrackSat_Entry(std::string jsonTLE)
{
    // Extract the data from the JSON string
    json oTLE = json::parse(jsonTLE);
    TLE_Name = oTLE["SATNAME"];
    TLE_LineA = oTLE["TLEA"];
    TLE_LineB = oTLE["TLEB"];
    TLE_Table = oTLE["TABLE"];

    // Get the rest of the needed data from the config file
    observerLatitude = stof(sConfigHandler_Observer_Latitude());
    observerLongitude = stof(sConfigHandler_Observer_Longitude());

    // Create SGP4 Object
    Observer obsObj(observerLatitude, observerLongitude, 0);
    Tle tleObj = Tle(TLE_Name, TLE_LineA, TLE_LineB);
    SGP4 sgp4Obj(tleObj);

    // Get Info on Serial Port
    serPort = sConfigHandler_ReadSerialPort();
    serBaud = sConfigHandler_ReadBaudrate();

    // Open Serial Port
    std::cout << "Port: " << serPort << std::endl << "Baud: " << stoi(serBaud) << std::endl;
    serial::Serial serObj(serPort, stoi(serBaud));
    if (serObj.isOpen())
    {
        // Serial port is open
        std::cout << clrmgr::green << "Serial port opened." << clrmgr::reset << std::endl;
    } else
    {
        // Serial port is not open, exit
        std::cout << clrmgr::red << "Serial port could not be opened, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        // Continue working on forming SGP4 Object
        DateTime cDT = DateTime::Now(true);
        Eci eciObj = sgp4Obj.FindPosition(cDT);
        CoordTopocentric topoObj = obsObj.GetLookAngle(eciObj);
        CoordGeodetic geoObj = eciObj.ToGeodetic();

        // Get current position information on satellite
        currSat_Azimuth = Util::RadiansToDegrees(topoObj.azimuth);
        currSat_Elevation = Util::RadiansToDegrees(topoObj.elevation);
        currSat_Range = topoObj.range;
        currSat_RangeRate = topoObj.range_rate;
        currSat_Latitude = Util::RadiansToDegrees(geoObj.latitude);
        currSat_Longitude = Util::RadiansToDegrees(geoObj.longitude);
        currSat_Altitude = geoObj.altitude;

        // Calculate whether satellite is in AOS or LOS
        if (currSat_Elevation > 0.0)
        {
            // Satellite is in AOS
            std::cout << "AOS" << std::endl;
        } else
        {
            // Satellite is in LOS
            std::cout << "LOS" << std::endl;
        }

        // Add to msgCount
        msgCount++;

        // Form JSON String with data
        json jSatObj;
        jSatObj["AZIMUTH"] = floatToStr(currSat_Azimuth);
        jSatObj["ELEVATION"] = floatToStr(currSat_Elevation);
        jSatObj["RANGE"] = floatToStr(currSat_Range);
        jSatObj["RANGERATE"] = floatToStr(currSat_RangeRate);
        jSatObj["LATITUDE"] = floatToStr(currSat_Latitude);
        jSatObj["LONGITUDE"] = floatToStr(currSat_Longitude);
        jSatObj["ALTITUDE"] = floatToStr(currSat_Altitude);
        jSatObj["MSGCOUNT"] = std::to_string(msgCount);

        // Fix JSON String
        std::string sSatJson = jSatObj.dump() + "\r\n";

        std::cout << sSatJson << std::endl;

        // Send JSON String over serial port
        size_t bytesWritten = serObj.write(sSatJson);

        // TODO WAIT
        usleep (1 * 1000000);
    }
}
