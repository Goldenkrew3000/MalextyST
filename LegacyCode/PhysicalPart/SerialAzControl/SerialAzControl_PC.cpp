/*
// Serial Library - Enumerate ports, and selector
// Modified to work with MSVC
// Malexty 2021
*/


/*
// Current issues with code:
// If user enters non numberic number, it kinda goes crazy
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <math.h>
#include "serial/serial.h" // https://github.com/wjwwood/serial

#include "SGP4/CoordTopocentric.h"
#include "SGP4/CoordGeodetic.h"
#include "SGP4/Observer.h"
#include "SGP4/Util.h"
#include "SGP4/SGP4.h"

unsigned int microsecond = 1000000;

float observerLat = -27.5597;
float observerLon = 151.9503;

std::string NOAA19_TLE_L1 = "NOAA 19 [+]             ";
std::string NOAA19_TLE_L2 = "1 33591U 09005A   22013.01175577  .00000065  00000+0  60432-4 0  9995";
std::string NOAA19_TLE_L3 = "2 33591  99.1671  43.7386 0013006 264.1752  95.7937 14.12521623666504";

// Counters
int counter = 0;
int userCounter = 0;
int msgCount = 0;

// Variables
std::string rComPort = "";

std::string enumerate_ports()
{
	std::vector<serial::PortInfo> devices_found = serial::list_ports();
	std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

	int devicesFound = devices_found.size();
	std::cout << "Devices found (length of vector): " << devicesFound << std::endl;

	std::vector<std::string> sPort;
	std::vector<std::string> sDescription;
	std::vector<std::string> sHardware;

	while (iter != devices_found.end())
	{
		userCounter = counter + 1;
		serial::PortInfo device = *iter++;

		sPort.push_back(device.port.c_str());
		sDescription.push_back(device.description.c_str());
		sHardware.push_back(device.hardware_id.c_str());

		std::cout << "Device: " << userCounter << std::endl;
		std::cout << "Port: " << device.port.c_str() << std::endl;
		std::cout << "Description: " << device.description.c_str() << std::endl;
		std::cout << "Hardware: " << device.hardware_id.c_str() << std::endl;
		std::cout << std::endl;

		counter++;
	}

	int uInput = 0;
	while (uInput == 0)
	{
		std::cout << "Which device do you want: ";
		std::cin >> uInput;
		if (uInput <= devicesFound && uInput > 0)
		{
			// Valid user input, continue
			break;
		}
		else
		{
			// Invalid user input, return to user input
			uInput = 0;
		}
	}

	std::cout << "Port: " << sPort[uInput - 1] << std::endl;
	std::cout << "Description: " << sDescription[uInput - 1] << std::endl;
	std::cout << "Hardware: " << sHardware[uInput - 1] << std::endl;

	return sPort[uInput - 1];
}

int main()
{
	// Entry point
	std::cout << "Serial Enumerate Ports and Selector" << std::endl;
	rComPort = enumerate_ports();
	std::cout << "End enumerate_ports() function" << std::endl;
	std::cout << "Returned Serial Port: " << rComPort << std::endl;

	std::cout << "Opening Serial Port " << rComPort << "..." << std::endl;
	serial::Serial oPort(rComPort, 9600);
	if (oPort.isOpen())
	{
		// Serial port is open
		std::cout << rComPort << " is open." << std::endl;
	}
	else
	{
		// Serial port is not open, exit
		std::cout << rComPort << " cannot be opened. Exiting..." << std::endl;
	}

	std::cout << "Entering sample send function" << std::endl;

	Observer obs(observerLat, observerLon, 0);
	Tle tle = Tle(NOAA19_TLE_L1, NOAA19_TLE_L2, NOAA19_TLE_L3);
	SGP4 sgp4(tle);

	while (1)
	{
		std::cout << "Sending message" << std::endl;

		// Add to msgCount
		msgCount++;

		// Sample data in same format as real program
		DateTime dt = DateTime::Now(true);
		Eci eci = sgp4.FindPosition(dt);
		CoordTopocentric topo = obs.GetLookAngle(eci);
		CoordGeodetic geo = eci.ToGeodetic();
		
		float az;
		float el;
		int iAz;
		int iEl;

		az = Util::RadiansToDegrees(topo.azimuth);
		el = Util::RadiansToDegrees(topo.elevation);

		iAz = round(az);
		iEl = round(el);

		std::cout << "s1 (az): (not rounded) " << az << " (rounded) " << iAz << std::endl;
		std::cout << "s2 (el): (not rounded) " << el << " (rounded) " << iEl << std::endl;
		
		std::string s1 = std::to_string(iAz) + "\r\n";
		std::string s2 = std::to_string(iEl) + "\r\n";
		std::string s3 = std::to_string(msgCount) + "\r\n";

		// Write to port
		size_t bytes_wrote0 = oPort.write("STARTMSG\r\n");
		size_t bytes_wrote1 = oPort.write(s1);
		size_t bytes_wrote2 = oPort.write(s2);
		size_t bytes_wrote3 = oPort.write(s3);
		size_t bytes_wrote4 = oPort.write("ENDMSG\r\n");

		std::cout << "Sent message" << std::endl << std::endl;

		// Sleep
		std::this_thread::sleep_for(std::chrono::microseconds(microsecond));
	}

	return 0;
}
