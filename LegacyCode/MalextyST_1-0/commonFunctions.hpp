/*
// Common Functions Library
// Malexty 2021
// This library makes it easier to implement simple functions into C++ programs
*/

#ifndef COMMONFUNCTIONS_HPP_INCLUDED
#define COMMONFUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <time.h>
#include <sys/stat.h>

namespace cmnfuncs
{
    inline void clearScreen()
    {
        // Clear Screen
        // Note: This function may seem simple but could change later as better
        // methods are found, so its easier to only have to change it once here
        system("clear");
    }

    inline std::string getUTCTime()
    {
        // This gets the UTC Time from the system for TLE Timestamping
        time_t ltime;
        time(&ltime);
        return std::to_string(ltime);
    }

    inline int doesFileExist(std::string filename)
    {
        // This function checks if the file exists in the argument
        // Returns a 0 if it doesnt, 1 if it does
        // Code from: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c (User: Ramon La Pietra)
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    }
}

#endif
