// C++ Imports
#include <iostream>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mGenConfig.hpp"
#include "sGenConfig.hpp"

// mGenConfig - Entry Point
void mGenConfig_Entry()
{
    // Generate Config Entry
    mGenConfig_PrintMenu();

    // Go to the system component
    sGenConfig_Entry();
}

// mGenConfig - Print Menu
void mGenConfig_PrintMenu()
{
    // Clear Screen
    cmnfuncs::clearScreen();

    // Print Menu
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker - Generate Config" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}
