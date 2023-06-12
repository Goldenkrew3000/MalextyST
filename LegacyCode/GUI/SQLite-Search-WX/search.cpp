#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <sqlite3.h>
#include "search.hpp"
#include "json.hpp"
#include "colorManager.hpp"

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

void searchSQLDB(std::string searchTerm)
{
    // Reset variables
    tableNumber = 0;
    callbackStage = 1;
    counter = 0;
    userCounter = 0;

    // Empty vectors
    aTleName.clear();
    aTleLineA.clear();
    aTleLineB.clear();
    aTleLocation.clear();

    // Create SQLite3 Objects
    sqlite3* sSearchDB_DB;
    char* sSearchDB_messageError;

    // Prepare SQLite Querys
    std::string qNasabareSearch = "SELECT * FROM NASABARE WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qAmateurSearch = "SELECT * FROM AMATEUR WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qCubesatSearch = "SELECT * FROM CUBESAT WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qGalileoSearch = "SELECT * FROM GALILEO WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qGloopsSearch = "SELECT * FROM GLOOPS WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qGpsopsSearch = "SELECT * FROM GPSOPS WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qIridiumSearch = "SELECT * FROM IRIDIUM WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qIridiumnextSearch = "SELECT * FROM IRIDIUMNEXT WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qMolniyaSearch = "SELECT * FROM MOLNIYA WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qNoaaSearch = "SELECT * FROM NOAA WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qScienceSearch = "SELECT * FROM SCIENC WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qTlenewSearch = "SELECT * FROM TLENEW WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qVisualSearch = "SELECT * FROM VISUAL WHERE NAME LIKE '%" + searchTerm + "%';";
    std::string qWeatherSearch = "SELECT * FROM WEATHER WHERE NAME LIKE '%" + searchTerm + "%';";

    // Open database
    std::string databaseName = "satellites.db";
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
}

std::vector<std::string> retName()
{
    return aTleName;
}

std::vector<std::string> retTLEA()
{
    return aTleLineA;
}

std::vector<std::string> retTLEB()
{
    return aTleLineB;
}

std::vector<std::string> retTLETable()
{
    return aTleLocation;
}
