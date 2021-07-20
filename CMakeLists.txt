cmake_minimum_required(VERSION 3.14)
project(TwitterLib LANGUAGES CXX)

include(GNUInstallDirs)

option(LTO "Turn Link Time Optimization ON/OFF" ON)

# Link-Time Optimization
include(CheckIPOSupported)
check_ipo_supported(RESULT has_lto OUTPUT error)
if(has_lto AND LTO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    message("LTO Enabled Globally")
elseif(NOT has_lto)
    message(WARNING "LTO is not supported: ${error}")
else()
    message("LTO Not Enabled")
endif()

# Subdirectories
add_subdirectory(networklib)
add_subdirectory(twitterlib)
add_subdirectory(demos)
add_subdirectory(tests)

add_custom_target(twitterlib.all
    DEPENDS
        networklib
        twitterlib
        twitterlib.tests
        twitterlib.demos
)

