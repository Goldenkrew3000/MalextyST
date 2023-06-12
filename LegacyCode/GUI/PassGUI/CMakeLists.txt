cmake_minimum_required(VERSION 3.13)
project(wxgui-test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES    "main.cpp"
                    "window.cpp"
                    "search.cpp"
                    "predict.cpp"
)

add_executable(wxgui-test ${SOURCE_FILES})

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

# WXWidgets
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

# SQLite3
find_package(SQLite3 REQUIRED)
include_directories(${PROJECT_SOURCE_DIR} ${SQlite3_INCLUDE_DIRS})

target_link_libraries(wxgui-test ${wxWidgets_LIBRARIES} ${SQLite3_LIBRARIES} sgp4)
# had PRIVATE next to wxgui-test