cmake_minimum_required(VERSION 3.14)
project(TwitterLib LANGUAGES CXX)

include(GNUInstallDirs)

# Dependencies
find_package(Boost 1.58.0 REQUIRED COMPONENTS system iostreams)
add_library(boost INTERFACE IMPORTED)
target_include_directories(boost INTERFACE ${Boost_INCLUDE_DIR})
target_link_libraries(boost INTERFACE ${Boost_LIBRARIES})

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
