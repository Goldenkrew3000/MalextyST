/**
// Color Manager Header Library
// Malexty 2021
// This library just makes it easy to implement ANSI color into C++ programs
*/

#ifndef COLORMANAGER_HPP_INCLUDED
#define COLORMANAGER_HPP_INCLUDED

#include <iostream>
#include <cstdio>

namespace clrmgr
{
    inline std::ostream& green(std::ostream& stream)
    {
        // ANSI Bright Green
        stream << "\033[92m";
        return stream;
    }

    inline std::ostream& red(std::ostream& stream)
    {
        // ANSI Bright Red
        stream << "\033[91m";
        return stream;
    }

    inline std::ostream& magenta(std::ostream& stream)
    {
        // ANSI Magenta
        stream << "\033[35m";
        return stream;
    }

    inline std::ostream& yellow(std::ostream& stream)
    {
        // ANSI Bright Yellow
        stream << "\033[33m";
        return stream;
    }

    inline std::ostream& blue(std::ostream& stream)
    {
        // ANSI Bright Blue
        stream << "\033[94m";
        return stream;
    }

    inline std::ostream& reset(std::ostream& stream)
    {
        // ANSI Reset
        stream << "\033[00m";
        return stream;
    }

    inline std::ostream& underline(std::ostream& stream)
    {
        // ANSI Underline
        stream << "\033[4m";
        return stream;
    }
}

#endif
