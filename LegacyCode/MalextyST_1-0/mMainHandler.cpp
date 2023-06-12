// C++ Imports
#include <iostream>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mMainHandler.hpp"

void mMainHandler_PrintMenu()
{
    // Clear screen
    cmnfuncs::clearScreen();
 
    // Print menu
    std::cout << "---------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "c) Change configuration" << std::endl;
    std::cout << "g) Generate new configuration" << std::endl;
    std::cout << "u) Update TLEs" << std::endl;
    std::cout << "a) Check TLE Age" << std::endl;
    std::cout << "t) Track Satellite" << std::endl;
    std::cout << "e) Exit Program" << std::endl;
}
