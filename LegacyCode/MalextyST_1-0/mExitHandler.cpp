// C++ Imports
#include <iostream>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mExitHandler.hpp"

void mExitHandler_Exit()
{
    // Clear Screen
    cmnfuncs::clearScreen();

    // Print message
    std::cout << "----------------------------------" << std::endl;
    std::cout << "MalextyST Satellite Tracker - Exit" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Thank you for using!" << std::endl;

    // Exit with code 0
    exit(0);
}
