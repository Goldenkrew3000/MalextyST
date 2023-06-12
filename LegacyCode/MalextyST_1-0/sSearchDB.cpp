// C++ Imports
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <sqlite3.h>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"
#include "json.hpp"

// Program Parts Imports
#include "sSearchDB.hpp"
#include "sConfigHandler.hpp"

// Setup
using json = nlohmann::json;

// Variables to keep track of SQL search queries
int tableNumber = 0;
int callbackStage = 1;
int counter = 0;
int userCounter = 0;

// Vectors to store TLE data
std::vector<std::string> aTleName;
std::vector<std::string> aTleLineA;
std::vector<std::string> aTleLineB;
std::vector<std::string> aTleLocation;

// Callback function for SQLite queries
static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    
    for (i = 0; i < argc; i++)
    {
        if (callbackStage == 1)
        {
            aTleName.push_back(argv[i]);

            if (tableNumber == 1)
            {
                aTleLocation.push_back("Nasabare");
            } else if (tableNumber == 2)
            {
                aTleLocation.push_back("Amateur");
            } else if (tableNumber == 3)
            {
                aTleLocation.push_back("Cubesat");
            } else if (tableNumber == 4)
            {
                aTleLocation.push_back("Galileo");
            } else if (tableNumber == 5)
            {
                aTleLocation.push_back("Gloops");
            } else if (tableNumber == 6)
            {
                aTleLocation.push_back("Gpsops");
            } else if (tableNumber == 7)
            {
                aTleLocation.push_back("Iridium");
            } else if (tableNumber == 8)
            {
                aTleLocation.push_back("Iridiumnext");
            } else if (tableNumber == 9)
            {
                aTleLocation.push_back("Molniya");
            } else if (tableNumber == 10)
            {
                aTleLocation.push_back("Noaa");
            } else if (tableNumber == 11)
            {
                aTleLocation.push_back("Science");
            } else if (tableNumber == 12)
            {
                aTleLocation.push_back("Tlenew");
            } else if (tableNumber == 13)
            {
                aTleLocation.push_back("Visual");
            } else if (tableNumber == 14)
            {
                aTleLocation.push_back("Weather");
            }

            callbackStage = 2;
        } else if (callbackStage == 2)
        {
            aTleLineA.push_back(argv[i]);
            callbackStage = 3;
        } else if (callbackStage == 3)
        {
            aTleLineB.push_back(argv[i]);
            callbackStage = 1;
            counter++;
        }
    }

    return 0;
}

// Function to search and get the TLE of the desired satellite from the database
std::string sSearchDB_GetTLE(std::string searchTerm)
{
    // Create SQLite3 Objects
    sqlite3* sSearchDB_DB;
    char* sSearchDB_messageError;

    // Prepare SQLite Querys
    std::string qNasabareSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Nasabare() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qAmateurSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Amateur() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qCubesatSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Cubesat() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qGalileoSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Galileo() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qGloopsSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Gloops() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qGpsopsSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Gpsops() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qIridiumSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Iridium() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qIridiumnextSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Iridiumnext() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qMolniyaSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Molniya() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qNoaaSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Noaa() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qScienceSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Science() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qTlenewSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Tlenew() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qVisualSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Visual() + " WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qWeatherSearch = "SELECT * FROM " + sConfigHandler_SETNAME_Weather() + " WHERE NAME LIKE '%" + searchTerm + "%';";

    // Open database
    std::string databaseName = sConfigHandler_TLESETTING_DBName();
    int sqlExit = sqlite3_open(databaseName.c_str(), &sSearchDB_DB);

    // Search database for search term
    tableNumber = 1;
    sqlExit = sqlite3_exec(sSearchDB_DB, qNasabareSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search Nasabare table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Nasabare table." << clrmgr::reset << std::endl;
    }

    tableNumber = 2;
    sqlExit = sqlite3_exec(sSearchDB_DB, qAmateurSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Amateur table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Amateur table." << clrmgr::reset << std::endl;
    }

    tableNumber = 3;
    sqlExit = sqlite3_exec(sSearchDB_DB, qCubesatSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Cubesat table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Cubesat table." << clrmgr::reset << std::endl;
    }

    tableNumber = 4;
    sqlExit = sqlite3_exec(sSearchDB_DB, qGalileoSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Galileo table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Galileo table." << clrmgr::reset << std::endl;
    }

    tableNumber = 5;
    sqlExit = sqlite3_exec(sSearchDB_DB, qGloopsSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Gloops table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Gloops table." << clrmgr::reset << std::endl;
    }

    tableNumber = 6;
    sqlExit = sqlite3_exec(sSearchDB_DB, qGpsopsSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Gpsops table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Gpsops table." << clrmgr::reset << std::endl;
    }

    tableNumber = 7;
    sqlExit = sqlite3_exec(sSearchDB_DB, qIridiumSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Iridium table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Iridium table." << clrmgr::reset << std::endl;
    }

    tableNumber = 8;
    sqlExit = sqlite3_exec(sSearchDB_DB, qIridiumnextSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Iridiumnext table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Iridiumnext table." << clrmgr::reset << std::endl;
    }

    tableNumber = 9;
    sqlExit = sqlite3_exec(sSearchDB_DB, qMolniyaSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Molniya table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Molniya table." << clrmgr::reset << std::endl;
    }

    tableNumber = 10;
    sqlExit = sqlite3_exec(sSearchDB_DB, qNoaaSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Noaa table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Noaa table." << clrmgr::reset << std::endl;
    }

    tableNumber = 11;
    sqlExit = sqlite3_exec(sSearchDB_DB, qScienceSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Science table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Science table." << clrmgr::reset << std::endl;
    }

    tableNumber = 12;
    sqlExit = sqlite3_exec(sSearchDB_DB, qTlenewSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Tlenew table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Tlenew table." << clrmgr::reset << std::endl;
    }

    tableNumber = 13;
    sqlExit = sqlite3_exec(sSearchDB_DB, qVisualSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Visual table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Visual table." << clrmgr::reset << std::endl;
    }

    tableNumber = 14;
    sqlExit = sqlite3_exec(sSearchDB_DB, qWeatherSearch.c_str(), callback, 0, &sSearchDB_messageError);
    if (sqlExit != SQLITE_OK)
    {
        // Failed to search the Weather table
        std::cout << clrmgr::magenta << "SQLSearch: " << clrmgr::red << "Failed to search the Weather table." << clrmgr::reset << std::endl;
    }
    
    // Display data to user
    std::cout << "Total number of satellites found: " << aTleName.size() << std::endl;
    for (int a = 0; a < aTleName.size(); a++)
    {
        std::cout << "ID: " + std::to_string(a) + " (" + aTleLocation[a] + ") " + aTleName[a] << std::endl;
    }
    
    // Check if we found any satellites with the search term in the database
    if (aTleName.size() <= 0)
    {
        // Found no satellites, close database and exit (Clears up a lot of memory leaks)
        std::cout << clrmgr::red << "No satellites found within database, exiting." << clrmgr::reset << std::endl;
        sqlite3_close(sSearchDB_DB);
        exit(EXIT_FAILURE);
    }

    // Get satellite that user wants to use
    std::cout << "Enter ID of satellite to use: ";
    std::string sUserID = "";
    std::cin >> sUserID;
    int userID = stoi(sUserID);
    if (userID >= 0 && userID < aTleName.size())
    { /* User entered a correct ID, ignore */ } else
    {
        // User did not enter a correct ID, close database and exit
        std::cout << clrmgr::red << "You did not enter a valid ID, exiting." << clrmgr::reset << std::endl;
        sqlite3_close(sSearchDB_DB);
        exit(EXIT_FAILURE);
    }

    // From this point on, it has been verified that the user has entered a correct ID
    // Form JSON string with Satellite information
    json satObj;
    satObj["SATNAME"] = aTleName[userID];
    satObj["TLEA"] = aTleLineA[userID];
    satObj["TLEB"] = aTleLineB[userID];
    satObj["TABLE"] = aTleLocation[userID];
    
    // Close the database
    sqlite3_close(sSearchDB_DB);

    // Return JSON string of the selected satellite TLE data
    return satObj.dump();
}
