// C++ Imports
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"
#include "json.hpp"

// Library Imports
#include <Serial/include/serial.h>

// Program Parts Imports
#include "sSerialHandler.hpp"

// Serial Vectors
std::vector<std::string> enumPort;
std::vector<std::string> enumDesc;
std::vector<std::string> enumHwId;

// Variables
std::string userPortNum;

// sSerialHandler_Enumerate - Enumerate all serial ports
std::string sSerialHandler_Enumerate()
{
    // Find devices
    std::vector<serial::PortInfo> devicesFound = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devicesFound.begin();

    // Loop through found devices to add them to the enum vectors
    while (iter != devicesFound.end())
    {
        serial::PortInfo device = *iter++;
        enumPort.push_back(device.port.c_str());
        enumDesc.push_back(device.description.c_str());
        enumHwId.push_back(device.hardware_id.c_str());
    }

    // List amount of serial ports found, and the ports
    std::cout << "Amount of serial ports found: " << enumPort.size() << std::endl;
    for (int portIter = 0; portIter < enumPort.size(); portIter++)
    {
        std::cout << "(" << portIter << ") " << enumPort[portIter] << std::endl;
    }

    // Get port that user wants to use
    std::cout << "Enter ID of Serial Port to use: ";
    std::cin >> userPortNum;

    // Check if user entered a valid port ID
    if (stoi(userPortNum) >= 0 && stoi(userPortNum) < enumPort.size())
    { /* User entered a valid serial port ID, ignore */ } else
    {
        // User did not enter a valid serial port ID, exit
        std::cout << clrmgr::red << "You did not enter a correct Serial Port ID, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Return serial port that user selected
    return enumPort[stoi(userPortNum)];
}
