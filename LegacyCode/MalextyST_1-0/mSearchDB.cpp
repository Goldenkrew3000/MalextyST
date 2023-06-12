// C++ Imports
#include <iostream>
#include <cstdlib>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mSearchDB.hpp"
#include "sSearchDB.hpp"
#include "sConfigHandler.hpp"
#include "sTrackSat.hpp"
#include "sFileHandler.hpp"

// TEST
#include "sSerialHandler.hpp"

// mSearchDB - Entry Point
void mSearchDB_Entry()
{
    // Print menu
    mSearchDB_PrintMenu();

    // Prepare Configuration File
    sConfigHandler_ParseConfig();

    // Check if database file exists
    if (sFileHandler_checkSatDBExist())
    { /* Database exists, ignore */ } else
    {
        // Database does not exist, exit
        std::cout << clrmgr::red << "Database does not exist, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get user to input search term
    std::string searchTerm = "";
    std::cout << "Satellite Search Term: ";
    std::cin >> searchTerm;
    
    // Get Satellite TLE from search term
    std::string satTLEJson = sSearchDB_GetTLE(searchTerm);

    // Send TLE over to satellite tracking part of program
    sTrackSat_Entry(satTLEJson);

    //sSerialHandler_Enumerate();
}

// mSearchDB - Print Menu
void mSearchDB_PrintMenu()
{
    // Clear Screen
    cmnfuncs::clearScreen();

    // Print menu
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker - Track Satellite" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}
