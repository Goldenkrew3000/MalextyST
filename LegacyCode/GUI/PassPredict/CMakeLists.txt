cmake_minimum_required(VERSION 3.13)
project(predict-next)
set(CMAKE_CXX_STANDARD 14) # Sets to C++14, might have to change this later
set(CMAKE_BUILD_TYPE Debug) # Build binary with debug symbols

# Add files to be compiled
set(SOURCE_FILES    "main.cpp"
)

# Add the executable
# Note: This has to be here for SPECIFICALLY the serial library *cough* *cough*
add_executable(predict-next ${SOURCE_FILES})

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
target_link_libraries(predict-next ${CURL_LIBRARIES} ${SQLite3_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} sgp4)
