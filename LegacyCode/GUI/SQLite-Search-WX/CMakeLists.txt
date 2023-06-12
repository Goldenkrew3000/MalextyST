cmake_minimum_required(VERSION 3.13)
project(wxgui-test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES    "main.cpp"
                    "window.cpp"
                    "search.cpp"
)

add_executable(wxgui-test ${SOURCE_FILES})

# WXWidgets
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

# SQLite3
find_package(SQLite3 REQUIRED)
include_directories(${SQlite3_INCLUDE_DIRS})


target_link_libraries(wxgui-test PRIVATE ${wxWidgets_LIBRARIES} ${SQLite3_LIBRARIES})
