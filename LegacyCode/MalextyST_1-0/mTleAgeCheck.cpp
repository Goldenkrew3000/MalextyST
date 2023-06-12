// C++ Imports
#include <iostream>
#include <string>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mTleAgeCheck.hpp"
#include "sTleAgeCheck.hpp"

// mTleAgeCheck - Entry Point
void mTleAgeCheck_Entry()
{
    // Print menu
    mTleAgeCheck_PrintMenu();

    // Check TLE age
    sTleAgeCheck_Check();
}

// mTleAgeCheck - Print Menu
void mTleAgeCheck_PrintMenu()
{
    // Clear Screen
    cmnfuncs::clearScreen();

    // Print menu
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker - TLE Age Check" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}
