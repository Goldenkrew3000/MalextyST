// C++ Imports
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sqlite3.h>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "sTleAgeCheck.hpp"
#include "sConfigHandler.hpp"

// Objects and variables
sqlite3* ageDB;
char* ageMessageError;
std::string sTimestamp = "";

std::string sqlitePullMetadata(std::string dbName);

static int callback(void* data, int argc, char** argv, char** azColName)
{
    // Put timestamp into variable
    sTimestamp = argv[0];

    return 0;
}

void sTleAgeCheck_Check()
{
    // Parse config file (Note: This function also checks if the config file exists, and handles it)
    sConfigHandler_ParseConfig();

    // Get the filename of the TLE database
    std::string dbFilename = sConfigHandler_TLESETTING_DBName();

    // Check if the database exists
    // Note: This is the first time this new function from commonFunctions is being used in this program
    int dbExist = cmnfuncs::doesFileExist(dbFilename);
    if (dbExist == 0)
    {
        // Database does not exist, exit
        std::cout << clrmgr::red << "Database not found, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    } else if (dbExist == 1)
    {
        // Database exists
        std::cout << clrmgr::green << "Database found." << clrmgr::reset << std::endl;
    }

    // Pull the metadata from the database
    std::string dbUnixTimestamp = sqlitePullMetadata(dbFilename);

    // Get current UNIX timestamp
    std::string cUnixTimestamp = cmnfuncs::getUTCTime();

    // Convert the UNIX timestamps from std::string to time_t
    const char* dbunix_str = dbUnixTimestamp.c_str();
    time_t db_timestamp = (time_t) strtol(dbunix_str, NULL, 10);
    const char* cunix_str = cUnixTimestamp.c_str();
    time_t c_timestamp = (time_t) strtol(cunix_str, NULL, 10);

    // Convert the time_t timestamps to a readable format
    char db_timebuf[80];
    struct tm db_ts;
    db_ts = *localtime(&db_timestamp);
    strftime(db_timebuf, sizeof(db_timebuf), "%a %Y-%m-%d %H:%M:%S %Z", &db_ts);
    char c_timebuf[80];
    struct tm c_ts;
    c_ts = *localtime(&c_timestamp);
    strftime(c_timebuf, sizeof(c_timebuf), "%a %Y-%m-%d %H:%M:%S %Z", &c_ts);

    // Calculate the amount of time between the 2 dates
    double tleUpdateTime = std::difftime(c_timestamp, db_timestamp) / (60 * 60 * 24);
    std::cout << "Time since updating TLEs: " << tleUpdateTime << " days." << std::endl;

    // Check if the user should update the TLEs yet
    if (tleUpdateTime > 7)
    {
        // Its been over 7 days, user should update
        std::cout << clrmgr::red << "It has been more than 7 days since a TLE update, please update." << clrmgr::reset << std::endl;
    } else
    {
        // Its has not been more than 7 days, user doesn't need to update
        std::cout << clrmgr::green << "It has been less than 7 days since a TLE update, not needed yet." << clrmgr::reset << std::endl;
    }
}

std::string sqlitePullMetadata(std::string dbName)
{
    // Initialize
    int sqlExit = sqlite3_open(dbName.c_str(), &ageDB);
    
    // Create Query to select METADATA table
    std::string sqlQuery = "SELECT * FROM METADATA;";

    // Fetch data from the database
    sqlExit = sqlite3_exec(ageDB, sqlQuery.c_str(), callback, 0, &ageMessageError);
    if (sqlExit != SQLITE_OK)
    {
        std::cout << clrmgr::red << "Data could not be fetched from database, exiting." << clrmgr::reset << std::endl;
        sqlite3_free(ageMessageError);
        sqlite3_close(ageDB);
        exit(EXIT_FAILURE);
    } else
    {
        std::cout << clrmgr::green << "Data fetched from database." << clrmgr::reset << std::endl;
    }

    // Close database
    sqlite3_close(ageDB);

    // Return UNIX timestamp
    return sTimestamp;
}
