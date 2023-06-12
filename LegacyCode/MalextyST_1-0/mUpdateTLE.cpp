// C++ Imports
#include <iostream>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mUpdateTLE.hpp"
#include "sUpdateTLE.hpp"

// mUpdateTLE - Entry Point
void mUpdateTLE_Entry()
{
    // Update TLE Entry
    mUpdateTLE_PrintMenu();
    std::cout << "Update TLE Entry" << std::endl;
    sUpdateTLE_Entry();
}

// mUpdateTLE - Print Menu
void mUpdateTLE_PrintMenu()
{
    // Clear Screen
    cmnfuncs::clearScreen();

    // Print Menu
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker - Update TLE" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}
