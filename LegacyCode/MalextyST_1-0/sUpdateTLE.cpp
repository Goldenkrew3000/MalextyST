// C++ Imports
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <curl/curl.h>
#include <sqlite3.h>
#include <sstream>
#include <fstream>
#include <vector>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"

// Program Parts Imports
#include "sUpdateTLE.hpp"
#include "sConfigHandler.hpp"
#include "sFileHandler.hpp"

// Objects and variables
CURL* curl;
CURLcode res;
std::string currentSet = "";
sqlite3* DB;
char* messageError;

// Write Function
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

// Progress function
int progressFunc(void* ptr, double tDown, double fDown, double tUp, double dUp)
{
    // Print downloaded bytes status
    std::cout << "\r" << clrmgr::magenta << "TleDownloader: " << clrmgr::blue << currentSet << ": " << clrmgr::reset << "Downloaded " << fDown << "/" << tDown << " bytes.";

    // Function has to return 0
    return 0;
}

void downloadTLE(std::string tleURL, std::string tempFold, std::string tleFile, std::string setName);
void sqliteApply(std::string dbName, std::string foldName, std::string tleName, std::string tableName);
void sqliteAddTimestamp(std::string dbName);

void sUpdateTLE_Entry()
{
    // Download TLEs
    std::cout << "Downloading TLEs" << std::endl;

    // Fill Config File Variables
    sConfigHandler_ParseConfig();

    // Create temporary folder for TLEs to be downloaded to
    if (sFileHandler_makeTempFolder())
    {
        // Temporary folder was created successfully
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::green << "Temp folder was created successfully." << clrmgr::reset << std::endl;
    } else
    {
        // Temporary folder was not created successfully
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::red << "Temp folder was not created successfully, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    }

    // Check if satellite DB exists
    bool doesSatDBExist = false;
    if (sFileHandler_checkSatDBExist())
    {
        // Satellite DB exists, will be deleted after successful TLE download
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::reset << "Satellite DB exists, will be deleted after successful TLE download." << std::endl;
        doesSatDBExist = true;
    } else
    {
        // Satellite DB does not exist, it will be created
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::reset << "Satellite DB does not exist, will be created." << std::endl;
    }

    // Get Variables
    std::string jTempFold = sConfigHandler_TLESETTING_TempFolderName();
    std::string jDBName = sConfigHandler_TLESETTING_DBName();

    // Download TLEs
    downloadTLE(sConfigHandler_TLEURL_Nasabare(), jTempFold, sConfigHandler_TLENAME_Nasabare(), sConfigHandler_SETNAME_Nasabare());
    downloadTLE(sConfigHandler_TLEURL_Amateur(), jTempFold, sConfigHandler_TLENAME_Amateur(), sConfigHandler_SETNAME_Amateur());
    downloadTLE(sConfigHandler_TLEURL_Cubesat(), jTempFold, sConfigHandler_TLENAME_Cubesat(), sConfigHandler_SETNAME_Cubesat());
    downloadTLE(sConfigHandler_TLEURL_Galileo(), jTempFold, sConfigHandler_TLENAME_Galileo(), sConfigHandler_SETNAME_Galileo());
    downloadTLE(sConfigHandler_TLEURL_Gloops(), jTempFold, sConfigHandler_TLENAME_Gloops(), sConfigHandler_SETNAME_Gloops());
    downloadTLE(sConfigHandler_TLEURL_Gpsops(), jTempFold, sConfigHandler_TLENAME_Gpsops(), sConfigHandler_SETNAME_Gpsops());
    downloadTLE(sConfigHandler_TLEURL_Iridium(), jTempFold, sConfigHandler_TLENAME_Iridium(), sConfigHandler_SETNAME_Iridium());
    downloadTLE(sConfigHandler_TLEURL_Iridiumnext(), jTempFold, sConfigHandler_TLENAME_Iridiumnext(), sConfigHandler_SETNAME_Iridiumnext());
    downloadTLE(sConfigHandler_TLEURL_Molniya(), jTempFold, sConfigHandler_TLENAME_Molniya(), sConfigHandler_SETNAME_Molniya());
    downloadTLE(sConfigHandler_TLEURL_Noaa(), jTempFold, sConfigHandler_TLENAME_Noaa(), sConfigHandler_SETNAME_Noaa());
    downloadTLE(sConfigHandler_TLEURL_Science(), jTempFold, sConfigHandler_TLENAME_Science(), sConfigHandler_SETNAME_Science());
    downloadTLE(sConfigHandler_TLEURL_Tlenew(), jTempFold, sConfigHandler_TLENAME_Tlenew(), sConfigHandler_SETNAME_Tlenew());
    downloadTLE(sConfigHandler_TLEURL_Visual(), jTempFold, sConfigHandler_TLENAME_Visual(), sConfigHandler_SETNAME_Visual());
    downloadTLE(sConfigHandler_TLEURL_Weather(), jTempFold, sConfigHandler_TLENAME_Weather(), sConfigHandler_SETNAME_Weather());

    // If satellite DB exists, delete it
    if (doesSatDBExist)
    {
        // Satellite DB exists, delete it
        if (sFileHandler_deleteSatDB())
        {
            // File was deleted successfully
            std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::green << "Old Satellite DB was deleted successfully." << std::endl;
        } else
        {
            // File was not deleted successfully
            std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::red << "Old Satellite DB was not deleted successfully, issues WILL occur." << std::endl;
            // Note: Could exit here, but would cause issues with the temp folder
        }
    }

    // Apply TLEs to SQLite Database
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Nasabare(), sConfigHandler_SETNAME_Nasabare());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Amateur(), sConfigHandler_SETNAME_Amateur());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Cubesat(), sConfigHandler_SETNAME_Cubesat());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Galileo(), sConfigHandler_SETNAME_Galileo());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Gloops(), sConfigHandler_SETNAME_Gloops());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Gpsops(), sConfigHandler_SETNAME_Gpsops());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Iridium(), sConfigHandler_SETNAME_Iridium());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Iridiumnext(), sConfigHandler_SETNAME_Iridiumnext());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Molniya(), sConfigHandler_SETNAME_Molniya());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Noaa(), sConfigHandler_SETNAME_Noaa());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Science(), sConfigHandler_SETNAME_Science());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Tlenew(), sConfigHandler_SETNAME_Tlenew());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Visual(), sConfigHandler_SETNAME_Visual());
    sqliteApply(jDBName, jTempFold, sConfigHandler_TLENAME_Weather(), sConfigHandler_SETNAME_Weather());

    // Add Metadata to SQLite Database
    sqliteAddTimestamp(jDBName);

    // Remove temporary folder
    if (sFileHandler_removeTempFolder())
    {
        // Temporary folder was removed
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::green << "Temp folder was deleted successfully." << clrmgr::reset << std::endl;
    } else
    {
        // Temporary folder was not deleted
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::red << "Temp folder was not deleted successfully, make sure to delete it manually." << clrmgr::reset << std::endl;
    }

    // Exit this function
    std::cout << "Downloaded TLEs." << std::endl;
}

void downloadTLE(std::string tleURL, std::string tempFold, std::string tleFile, std::string setName)
{
    // Initialize variables
    std::string responseString = "";
    long returnCode = 0;
    currentSet = setName;

    // Initialize cURL
    curl = curl_easy_init(); // Comment this line out to make cURL fail to initialize
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.81.0");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressFunc);

    // Download TLE
    if (curl)
    {
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::blue << setName + ": " << clrmgr::green << "Initialized cURL" << clrmgr::reset << std::endl;
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::blue << setName + ": " << clrmgr::reset << "Downloading " << setName << " TLE..." << std::endl;

        // Perform download on TLE
        curl_easy_setopt(curl, CURLOPT_URL, tleURL.c_str());
        res = curl_easy_perform(curl);

        // Get return code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &returnCode);

        // Print return code
        std::cout << " (Response Code: ";
        if (returnCode == 200 && res != CURLE_ABORTED_BY_CALLBACK)
        {
            std::cout << clrmgr::green << returnCode << clrmgr::reset;
        }
        else
        {
            std::cout << clrmgr::red << returnCode << clrmgr::reset;
        }
        std::cout << ")" << std::endl;

        // If return code is 0, exit (User is most likely not connected to the internet)
        if (returnCode == 0)
        {
            // Exit
            std::cout << clrmgr::red << "Error: Could not download TLE, exiting. (Are you connected to the internet?)" << clrmgr::reset << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // CURL failed to initialize
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::blue << setName << ": " << clrmgr::red << "cURL failed to initialize" << clrmgr::reset << std::endl;
    }

    // Write downloaded TLE to file
    std::string locFile = tempFold + "/" + tleFile;
    std::ofstream outTle(locFile, std::ios::binary);

    if (outTle)
    {
        // File opened, write
        outTle << responseString.c_str();
        outTle.close();

        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::blue << setName << ": " << clrmgr::green << "TLE saved." << clrmgr::reset << std::endl;
    }
    else
    {
        // File failed to open, exit
        std::cout << clrmgr::magenta << "TleDownloader: " << clrmgr::blue << setName << ": " << clrmgr::red << "Error opening location to save TLE..." << clrmgr::reset << std::endl;
        std::cout << clrmgr::red << "Error: Could not save TLE, exiting." << clrmgr::reset << std::endl;
        exit(EXIT_FAILURE);
    }

    // Cleanup cURL to avoid memory leaks
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void sqliteAddTimestamp(std::string dbName)
{
    // Initialize
    int exit = sqlite3_open(dbName.c_str(), &DB);
    int sqlSuccess = 0;
    int sqlFail = 0;
    std::string customQuery = "";

    // Create Table SQL Query
    std::string sqlCreate = "CREATE TABLE METADATA("
        "TIMESTAMP TEXT);";

    // Create SQL Table
    std::cout << clrmgr::magenta << "MetadataSqlite: " << clrmgr::blue << "TIMESTAMP: " << clrmgr::reset << "Creating SQL table..." << std::endl;
    exit = sqlite3_exec(DB, sqlCreate.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        std::cout << clrmgr::magenta << "MetadataSqlite: " << clrmgr::blue << "TIMESTAMP: " << clrmgr::red << "SQL table failed" << clrmgr::reset << std::endl;
    } else
    {
        std::cout << clrmgr::magenta << "MetadataSqlite: " << clrmgr::blue << "TIMESTAMP: " << clrmgr::green << "SQL table created" << clrmgr::reset << std::endl;
    }

    // Create custom query to add timestamp to metadata table
    customQuery = "INSERT INTO METADATA VALUES('" + cmnfuncs::getUTCTime() + "');";
    
    // Apply custom query to metadata table
    exit = sqlite3_exec(DB, customQuery.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        std::cout << clrmgr::magenta << "MetadataSqlite: " << clrmgr::blue << "TIMESTAMP: " << clrmgr::red << "Timestamp failed to be added to table." << clrmgr::reset << std::endl;
    } else
    {
        std::cout << clrmgr::magenta << "MetadataSqlite: " << clrmgr::blue << "TIMESTAMP: " << clrmgr::green << "Timestamp added to table." << clrmgr::reset << std::endl;
    }

    // Close database
    sqlite3_close(DB);
}

void sqliteApply(std::string dbName, std::string foldName, std::string tleName, std::string tableName)
{
    // Initialize
    int exit = sqlite3_open(dbName.c_str(), &DB);
    std::string locTle = foldName + "/" + tleName;
    std::ifstream fileObj(locTle.c_str());
    std::string fileLine = "";
    int fileLineCtr = 1;
    int sqlSuccess = 0;
    int sqlFail = 0;
    std::vector<std::string> tleA;
    std::vector<std::string> tleB;
    std::vector<std::string> tleC;
    std::string customQuery = "";

    // Create Table SQL Query
    std::string sqlCreate = "CREATE TABLE " + tableName + "("
        "NAME TEXT,"
        "TLE1 TEXT,"
        "TLE2 TEXT);";

    // Create SQL Table
    std::cout << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::reset << "Creating SQL table..." << std::endl;
    exit = sqlite3_exec(DB, sqlCreate.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        std::cout << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::red << "SQL table failed" << clrmgr::reset << std::endl;
        sqlite3_free(messageError);
    } else
    {
        std::cout << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::green << "SQL table created" << clrmgr::reset << std::endl;
    }

    // Fill TLE vectors with TLEs
    while (std::getline(fileObj, fileLine))
    {
        // Remove the \r from the line before putting it into the database (Makes it a lot easier to deal with later)
        if (!fileLine.empty() && fileLine[fileLine.size() - 1] == '\r')
        {
            fileLine.erase(fileLine.size() - 1);
        }

        if (fileLineCtr == 1)
        {
            tleA.push_back(fileLine);
            fileLineCtr = 2;
        }
        else if (fileLineCtr == 2)
        {
            tleB.push_back(fileLine);
            fileLineCtr = 3;
        }
        else if (fileLineCtr == 3)
        {
            tleC.push_back(fileLine);
            fileLineCtr = 1;
        }
    }

    // Fill SQL table with TLE Vector contents
    for (int a = 0; a < tleA.size(); a++)
    {
        // Create custom query
        customQuery = "INSERT INTO " + tableName + " VALUES('" + tleA[a] + "', '" + tleB[a] + "', '" + tleC[a] + "');";
        
        // Apply custom query to SQL database
        exit = sqlite3_exec(DB, customQuery.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK)
        {
            sqlFail++;
            std::cout << "\r" << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::reset << "Satellites Written: " << sqlSuccess << "/" << sqlFail << std::flush;
            sqlite3_free(messageError);
        } else
        {
            sqlSuccess++;
            std::cout << "\r" << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::reset << "Satellites Written: " << sqlSuccess << "/" << sqlFail << std::flush;
        }

        // Reset custom query (probably not needed, but better to be safe than sorry)
        customQuery = "";
    }

    // Print newline to keep readable format
    std::cout << std::endl;

    // Print readable results
    if (sqlFail == 0)
    {
        std::cout << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::reset << "Stats: " << clrmgr::green << sqlSuccess << clrmgr::reset << "/" << clrmgr::red << sqlFail << clrmgr::reset << " (" << clrmgr::green << "Passed" << clrmgr::reset << ")" << std::endl;
    } else
    {
        std::cout << clrmgr::magenta << "TleSqlite: " << clrmgr::blue << tableName << ": " << clrmgr::reset << "Stats: " << clrmgr::green << sqlSuccess << clrmgr::reset << "/" << clrmgr::red << sqlFail << clrmgr::reset << " (" << clrmgr::red << "Failed" << clrmgr::reset << ")" << std::endl;
    }

    // Close file object
    fileObj.close();

    // Close database
    sqlite3_close(DB);
}
