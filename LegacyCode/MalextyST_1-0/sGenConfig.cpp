// C++ Imports
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"
#include "json.hpp"

// Program Parts Imports
#include "sGenConfig.hpp"
#include "dGenConfig.hpp"
#include "sSerialHandler.hpp"
#include "sFileHandler.hpp"

// Setup
using json = nlohmann::json;

// Variables
std::string uObsLatitude;
std::string uObsLongitude;
std::string uSerPort;

void sGenConfig_Entry()
{
    sGenConfig_GetData();
    //sGenConfig_GenObj();
}

void sGenConfig_GetData()
{
    //
    std::cout << "Fetch Required Info" << std::endl;
    
    // Get User Latitude
    std::cout << "Enter your latitude (e.x. -27.5598): ";
    std::cin >> uObsLatitude;

    // Get User Longitude
    std::cout << "Enter your longitude (e.x. 151.9507): ";
    std::cin >> uObsLongitude;

    // Get User Serial Port
    uSerPort = sSerialHandler_Enumerate();

    // Check if config file exists
    if (sFileHandler_checkConfigExists())
    {
        // Config file exists
        std::cout << "Previous config file found, will be deleted" << std::endl;
    }
}

void sGenConfig_GenObj()
{
    // Create JSON Object
    json newConfig_Obj;

    // Add URLs
    newConfig_Obj["TLE"]["URLS"]["NASABARE"] = def_tleUrlNasabare;
    newConfig_Obj["TLE"]["URLS"]["AMATEUR"] = def_tleUrlAmateur;
    newConfig_Obj["TLE"]["URLS"]["CUBESAT"] = def_tleUrlCubesat;
    newConfig_Obj["TLE"]["URLS"]["GALILEO"] = def_tleUrlGalileo;
    newConfig_Obj["TLE"]["URLS"]["GLOOPS"] = def_tleUrlGloops;
    newConfig_Obj["TLE"]["URLS"]["GPSOPS"] = def_tleUrlGpsops;
    newConfig_Obj["TLE"]["URLS"]["IRIDIUM"] = def_tleUrlIridium;
    newConfig_Obj["TLE"]["URLS"]["IRIDIUMNEXT"] = def_tleUrlIridiumnext;
    newConfig_Obj["TLE"]["URLS"]["MOLNIYA"] = def_tleUrlMolniya;
    newConfig_Obj["TLE"]["URLS"]["NOAA"] = def_tleUrlNoaa;
    newConfig_Obj["TLE"]["URLS"]["SCIENCE"] = def_tleUrlScience;
    newConfig_Obj["TLE"]["URLS"]["TLENEW"] = def_tleUrlTlenew;
    newConfig_Obj["TLE"]["URLS"]["VISUAL"] = def_tleUrlVisual;
    newConfig_Obj["TLE"]["URLS"]["WEATHER"] = def_tleUrlWeather;

    // Add Filenames
    newConfig_Obj["TLE"]["FILENAMES"]["NASABARE"] = def_tleFileNasabare;
    newConfig_Obj["TLE"]["FILENAMES"]["AMATEUR"] = def_tleFileAmateur;
    newConfig_Obj["TLE"]["FILENAMES"]["CUBESAT"] = def_tleFileCubesat;
    newConfig_Obj["TLE"]["FILENAMES"]["GALILEO"] = def_tleFileGalileo;
    newConfig_Obj["TLE"]["FILENAMES"]["GLOOPS"] = def_tleFileGloops;
    newConfig_Obj["TLE"]["FILENAMES"]["GPSOPS"] = def_tleFileGpsops;
    newConfig_Obj["TLE"]["FILENAMES"]["IRIDIUM"] = def_tleFileIridium;
    newConfig_Obj["TLE"]["FILENAMES"]["IRIDIUMNEXT"] = def_tleFileIridiumnext;
    newConfig_Obj["TLE"]["FILENAMES"]["MOLNIYA"] = def_tleFileMolniya;
    newConfig_Obj["TLE"]["FILENAMES"]["NOAA"] = def_tleFileNoaa;
    newConfig_Obj["TLE"]["FILENAMES"]["SCIENCE"] = def_tleFileScience;
    newConfig_Obj["TLE"]["FILENAMES"]["TLENEW"] = def_tleFileTlenew;
    newConfig_Obj["TLE"]["FILENAMES"]["VISUAL"] = def_tleFileVisual;
    newConfig_Obj["TLE"]["FILENAMES"]["WEATHER"] = def_tleFileWeather;

    // Add TLE Set Names
    newConfig_Obj["TLE"]["SETNAMES"]["NASABARE"] = def_tleSetnameNasabare;
    newConfig_Obj["TLE"]["SETNAMES"]["AMATEUR"] = def_tleSetnameAmateur;
    newConfig_Obj["TLE"]["SETNAMES"]["CUBESAT"] = def_tleSetnameCubesat;
    newConfig_Obj["TLE"]["SETNAMES"]["GALILEO"] = def_tleSetnameGalileo;
    newConfig_Obj["TLE"]["SETNAMES"]["GLOOPS"] = def_tleSetnameGloops;
    newConfig_Obj["TLE"]["SETNAMES"]["GPSOPS"] = def_tleSetnameGpsops;
    newConfig_Obj["TLE"]["SETNAMES"]["IRIDIUM"] = def_tleSetnameIridium;
    newConfig_Obj["TLE"]["SETNAMES"]["IRIDIUMNEXT"] = def_tleSetnameIridiumnext;
    newConfig_Obj["TLE"]["SETNAMES"]["MOLNIYA"] = def_tleSetnameMolniya;
    newConfig_Obj["TLE"]["SETNAMES"]["NOAA"] = def_tleSetnameNoaa;
    newConfig_Obj["TLE"]["SETNAMES"]["SCIENCE"] = def_tleSetnameScience;
    newConfig_Obj["TLE"]["SETNAMES"]["TLENEW"] = def_tleSetnameTlenew;
    newConfig_Obj["TLE"]["SETNAMES"]["VISUAL"] = def_tleSetnameVisual;
    newConfig_Obj["TLE"]["SETNAMES"]["WEATHER"] = def_tleSetnameWeather;

    // Add Serial Port Settings
    newConfig_Obj["SERIAL"]["PORT"] = def_serPort;
    newConfig_Obj["SERIAL"]["BAUDRATE"] = def_serBaud;

    // Add Observer Settings
    newConfig_Obj["OBSERVER"]["LATITUDE"] = def_obsLat;
    newConfig_Obj["OBSERVER"]["LONGITUDE"] = def_obsLon;

    //

    // Dump
    std::cout << newConfig_Obj.dump(4) << std::endl;
}
