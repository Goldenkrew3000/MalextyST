cmake_minimum_required(VERSION 3.13)
project(malextyst)
set(CMAKE_CXX_STANDARD 14) # Sets to C++14, might have to change this later
set(CMAKE_BUILD_TYPE Debug) # Build binary with debug symbols

# Add files to be compiled
set(SOURCE_FILES    "main.cpp"                      # Main entry point
                    "mMainHandler.cpp"              # (Menu) Main Handler
                    "mExitHandler.cpp"              # (Menu) Exit Handler
                    "mChangeConfigHandler.cpp"      # (Menu) Change Config Handler
                    "sConfigHandler.cpp"            # (System) Config Handler
                    "sFileHandler.cpp"              # (System) File Handler
                    "sUpdateTLE.cpp"                # (System) Update TLE Handler
                    "mUpdateTLE.cpp"                # (Menu) Update TLE Handler
                    "sGenConfig.cpp"                # (System) Generate Config Handler
                    "mGenConfig.cpp"                # (Menu) Generate Config Handler
                    "sTleAgeCheck.cpp"              # (System) Tle Age Check Handler
                    "mTleAgeCheck.cpp"              # (Menu) Tle Age Check Handler
                    "sChangeConfigHandler.cpp"      # (System) Change Config Handler
                    "mSearchDB.cpp"                 # (Menu) Search Database Handler
                    "sSearchDB.cpp"                 # (System) Search Database Handler
                    "sTrackSat.cpp"                 # (System) Track Satellite Handler
                    "sSerialHandler.cpp"            # (Serial) Serial Handler
                    )

# Add the executable
# Note: This has to be here for SPECIFICALLY the serial library *cough* *cough*
add_executable(malextyst ${SOURCE_FILES})

# Packages
# SGP4
# P.S. This is a custom library (https://github.com/dnwrnr/sgp4)
set(SGP4_CC_FILES   "SGP4/CoordGeodetic.cc"
                    "SGP4/CoordTopocentric.cc"
                    "SGP4/DateTime.cc"
                    "SGP4/DecayedException.cc"
                    "SGP4/Eci.cc"
                    "SGP4/Globals.cc"
                    "SGP4/Observer.cc"
                    "SGP4/OrbitalElements.cc"
                    "SGP4/SatelliteException.cc"
                    "SGP4/SGP4.cc"
                    "SGP4/SolarPosition.cc"
                    "SGP4/TimeSpan.cc"
                    "SGP4/Tle.cc"
                    "SGP4/TleException.cc"
                    "SGP4/Util.cc"
                    "SGP4/Vector.cc"
                    "SGP4/CoordGeodetic.h"
                    "SGP4/CoordTopocentric.h"
                    "SGP4/DateTime.h"
                    "SGP4/DecayedException.h"
                    "SGP4/Eci.h"
                    "SGP4/Globals.h"
                    "SGP4/Observer.h"
                    "SGP4/OrbitalElements.h"
                    "SGP4/SatelliteException.h"
                    "SGP4/SGP4.h"
                    "SGP4/SolarPosition.h"
                    "SGP4/TimeSpan.h"
                    "SGP4/Tle.h"
                    "SGP4/TleException.h"
                    "SGP4/Util.h"
                    "SGP4/Vector.h")

add_library(sgp4 ${SGP4_CC_FILES})

# Serial
# P.S. This is a custom library (https://github.com/wjwwood/serial)
set(SERIAL_CC_FILES "Serial/src/serial.cc"
                    "Serial/include/serial.h"
                    "Serial/include/v8stdint.h")

if (APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(FOUNDATION_LIBRARY Foundation)
endif()

if (APPLE)
    list(APPEND SERIAL_CC_FILES "Serial/src/impl/unix.cc")
    list(APPEND SERIAL_CC_FILES "Serial/src/impl/list_ports/list_ports_osx.cc")
elseif (UNIX)
    list(APPEND SERIAL_CC_FILES "Serial/src/impl/unix.cc")
    list(APPEND SERIAL_CC_FILES "Serial/src/impl/list_ports/list_ports_linux.cc")
endif()

add_library(serial ${SERIAL_CC_FILES})
if (APPLE)
    target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY}) 
elseif(UNIX)
    target_link_libraries(malextyst rt pthread)
endif()

# CURL
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

# SQLite3
find_package(SQLite3)

# Threads
find_package(Threads REQUIRED)

# Boost (Requires filesystem)
find_package(Boost 1.70 COMPONENTS program_options filesystem REQUIRED)

# Include main directory
include_directories(${PROJECT_SOURCE_DIR} ${CURL_INCLUDE_DIR} ${SQLite3_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

# Link all the target libraries
target_link_libraries(malextyst ${CURL_LIBRARIES} ${SQLite3_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} sgp4 serial)
