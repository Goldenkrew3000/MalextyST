// C++ Imports
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Library Imports
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

// Program Parts Imports
#include "sFileHandler.hpp"
#include "sConfigHandler.hpp"

// Variables
#include "common.hpp"

// Boost setup
namespace fs = boost::filesystem;

// Functions

// Function to read configuration file
std::string sFileHandler_ReadConfigFile()
{
    // Read config file into std::string
    // Open config file
    std::ifstream configIfstream(configFilename);

    // Check if ifstream could open config file
    if (!configIfstream)
    {
        // Config file did not open successfully
        std::cout << clrmgr::red << "Config file not found, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read config file into string
    std::string configFile((std::istreambuf_iterator<char>(configIfstream)), std::istreambuf_iterator<char>());

    // Return config file contents
    return configFile;
}

// Function to create the temporary folder
bool sFileHandler_makeTempFolder()
{
    // Make temporary folder for creating TLE database
    std::string folderName = sConfigHandler_TLESETTING_TempFolderName();
    int folderStatus = mkdir(folderName.c_str(), 0777); // Returns 0 if folder was created, seems to return -1 if folder exists
    if (folderStatus == 0)
    {
        // Folder was created successfully
        return true;
    } else
    {
        // Folder was not created successfully
        return false;
    }
}

// Function to delete the temporary folder
bool sFileHandler_removeTempFolder()
{
    // Create boost folder path
    fs::path folderPath = sConfigHandler_TLESETTING_TempFolderName();

    // Delete directory
    std::uintmax_t filesDeleted = fs::remove_all(folderPath);

    // Check if folder still exists
    bool doesFolderExist = fs::exists(folderPath);
    if (doesFolderExist)
    {
        // Temporary folder was not deleted
        return false;
    } else
    {
        // Temporary folder was deleted
        return true;
    }
}

// Function to check if the satellites database file exists
bool sFileHandler_checkSatDBExist()
{
    // Get Satellite DB filename
    std::string satFilename = sConfigHandler_TLESETTING_DBName();
    
    // Check if file exists
    if (fs::exists(satFilename))
    {
        // Satellites DB exists
        return true;
    } else
    {
        // Satellites DB does not exist
        return false;
    }
}

// Function to delete the satellites database file
bool sFileHandler_deleteSatDB()
{
    // Get Satellite DB filename
    std::string satFilename = sConfigHandler_TLESETTING_DBName();

    // Remove file
    fs::remove(satFilename);

    // Check if file exists
    if (fs::exists(satFilename))
    {
        // File was not successfully deleted
        return false;
    } else
    {
        // File was successfully deleted
        return true;
    }
}

// Function to check if the config file exists
bool sFileHandler_checkConfigExists()
{
    // Check if file exists
    if (fs::exists(configFilename))
    {
        // Config file exists
        return true;
    } else
    {
        // Config file does not exist
        return false;
    }
}

// Function to delete the config file
bool sFileHandler_deleteConfig()
{
    //
}

// Function to write the config file
bool sFileHandler_writeConfig()
{
    // Cke
}
