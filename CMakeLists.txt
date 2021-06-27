cmake_minimum_required(VERSION 3.2)
project(TwitterLib LANGUAGES CXX)

# BUILD OPTIONS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_compile_options(-Wall)

enable_testing()
include(GNUInstallDirs)

# EXTERNAL LIBRARIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
find_package(Boost 1.58.0 REQUIRED COMPONENTS system iostreams)
add_library(boost INTERFACE IMPORTED)
target_include_directories(boost INTERFACE ${Boost_INCLUDE_DIR})
target_link_libraries(boost INTERFACE ${Boost_LIBRARIES})

# SUBDIRECTORIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_subdirectory(networklib)
add_subdirectory(twitterlib)
add_subdirectory(demos)
add_subdirectory(tests)

# CLANG TIDY
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_custom_target(compile_commands ALL
    COMMAND [ -f ${CMAKE_SOURCE_DIR}/build/compile_commands.json ] &&
        mv ${CMAKE_SOURCE_DIR}/build/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json || :)

# DOXYGEN
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Doxyfile in project/doc : make doc
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

