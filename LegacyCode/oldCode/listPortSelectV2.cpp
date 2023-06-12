#include <iostream>
#include <cstdio>
#include <string>
#include "serial/serial.h"

int counter = 0;
int userCounter = 0;

void enumerate_ports()
{
    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

    // Lists 4, expected
    int devicesFound = devices_found.size();
    std::cout << "Length of vector: " << devicesFound << std::endl;
    
    if (devicesFound == 0)
    {
        // No serial ports found, exit
        std::cout << "No serial ports were detected on your system!" << std::endl;
        exit(0);
    } else
    {
        // Serial ports found
        std::string sPort[devicesFound];
        std::string sDescription[devicesFound];
        std::string sHardware[devicesFound];

        while (iter != devices_found.end())
        {
            userCounter = counter + 1;
            serial::PortInfo device = *iter++;

            sPort[counter] = device.port.c_str();
            sDescription[counter] = device.description.c_str();
            sHardware[counter] = device.hardware_id.c_str();

            std::cout << "Device: " << userCounter << std::endl;
            std::cout << "Port: " << device.port.c_str() << std::endl;
            std::cout << "Description: " << device.description.c_str() << std::endl;
            std::cout << "Hardware: " << device.hardware_id.c_str() << std::endl;
            std::cout << std::endl;

            counter++;
        }

        int uInput;
        std::cout << "Which device do you want: ";
        std::cin >> uInput;
        
        std::cout << "Port: " << sPort[uInput - 1] << std::endl;
        std::cout << "Description: " << sDescription[uInput - 1] << std::endl;
        std::cout << "Hardware: " << sHardware[uInput - 1] << std::endl;
    }
}

int main()
{
    std::cout << "Serial Port Selector Program" << std::endl;
    enumerate_ports();
    std::cout << "END" << std::endl;
}
