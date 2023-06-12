/*
// Malexty Satellite Tracker (MalextyST)
// Version 0.2a
// Malexty 2021
// Purpose: Entry point to program
*/

// C++ Imports
#include <iostream>
#include <string>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "mMainHandler.hpp"
#include "mExitHandler.hpp"
#include "mChangeConfigHandler.hpp"
#include "mUpdateTLE.hpp"
#include "mGenConfig.hpp"
#include "mTleAgeCheck.hpp"
#include "mSearchDB.hpp"

// Variables
#include "common.hpp"
std::string configFilename = "config.json";

std::string mainInput;

int main()
{
    // Clear screen and print menu
    mMainHandler_PrintMenu();

    // Get user's input selection
    std::cout << "Option: ";
    std::cin >> mainInput;

    // Check if the user's selection is valid
    if (mainInput == "c")
    {
        // User selected 'Change configuration'
        mChangeConfigHandler_Entry();
    } else if (mainInput == "g")
    {
        // User selected 'Generate new configuration'
        mGenConfig_Entry();
    } else if (mainInput == "u")
    {
        // User selected 'Update TLEs'
        mUpdateTLE_Entry();
    } else if (mainInput == "a")
    {
        // User selected 'Check TLE Age'
        mTleAgeCheck_Entry();
    } else if (mainInput == "t")
    {
        // User selected 'Track Satellite'
        mSearchDB_Entry();
    } else if (mainInput == "e")
    {
        // User selected 'Exit Program'
        mExitHandler_Exit();
    } else
    {
        std::cout << clrmgr::red << "Error: Your input was invalid, exiting." << clrmgr::reset << std::endl;
        exit(1);
    }

    // End program
    return 0;
}
