cmake_minimum_required (VERSION 3.6)
project (TwitAPI)

# Build System Information For Clang-Tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(compile_commands ALL
	COMMAND [ -f ${CMAKE_SOURCE_DIR}/build/compile_commands.json ] &&
        mv ${CMAKE_SOURCE_DIR}/build/compile_commands.json
		${CMAKE_SOURCE_DIR}/compile_commands.json || :)

# Set Output Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib")

# Set Compiler Flags
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall")

# Your Include Directory
include_directories(include)

# Collect Source Files into Variable Names
set(TAL_SRC src/account.cpp src/app.cpp src/oauth.cpp src/request.cpp
          src/encode.cpp src/network.cpp src/response.cpp src/stream.cpp)

add_library(TAL STATIC ${TAL_SRC})

set(MAIN src/main.cpp)

# set(TEST_SOURCES test/test.cpp)

find_package(Boost 1.58.0 COMPONENTS system)
if(Boost_FOUND)
    add_executable(main ${MAIN})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

# Link libraries to executables
target_link_libraries(main TAL ${Boost_SYSTEM_LIBRARY} -lssl -lcrypto
    -pthread)
# target_link_libraries(tests gtest gtest_main ${Boost_SYSTEM_LIBRARY} -lssl
        # -lcrypto -pthread)

# Doxygen Target - Doxyfile in project/doc - make doc
find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
