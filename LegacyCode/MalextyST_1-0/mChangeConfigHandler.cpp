// C++ Imports
#include <iostream>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mChangeConfigHandler.hpp"
#include "sChangeConfigHandler.hpp"
#include "sConfigHandler.hpp"

// Functions

// mChangeConfigHandler - Entry Point
void mChangeConfigHandler_Entry()
{
    // Print menu
    mChangeConfigHandler_PrintMenu();

    // Parse config file (Will also check if config file exists, and handles it)
    sConfigHandler_ParseConfig();

    // Print config file settings
    mChangeConfigHandler_PrintSettings();
}

// mChangeConfigHandler - Print Menu
void mChangeConfigHandler_PrintMenu()
{
    // Clear screen
    cmnfuncs::clearScreen();
 
    // Print menu
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker - Change Configuration" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
}

//
void mChangeConfigHandler_PrintSettings()
{
    // Print settings
    std::cout << clrmgr::magenta << "Observer Settings" << clrmgr::reset << std::endl;
    std::cout << clrmgr::yellow << "Latitude: " << clrmgr::reset << sConfigHandler_Observer_Latitude() << std::endl;
    std::cout << clrmgr::yellow << "Longitude: " << clrmgr::reset << sConfigHandler_Observer_Longitude() << std::endl;
    std::cout << clrmgr::yellow << "Altitude: " << clrmgr::reset << sConfigHandler_Observer_Altitude() << std::endl;
    std::cout << clrmgr::magenta << "Serial Settings" << clrmgr::reset << std::endl;
    std::cout << clrmgr::yellow << "Serial Port: " << clrmgr::reset << sConfigHandler_ReadSerialPort() << std::endl;
    std::cout << clrmgr::yellow << "Serial Baudrate: " << clrmgr::reset << sConfigHandler_ReadBaudrate() << std::endl;
}
