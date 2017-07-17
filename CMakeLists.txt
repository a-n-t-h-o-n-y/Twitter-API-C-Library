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
          src/encode.cpp src/network.cpp src/stream.cpp src/status_line.cpp
          src/headers.cpp src/message.cpp src/parse.cpp src/hashtag.cpp
          src/size.cpp src/sizes.cpp src/url.cpp src/user_mention.cpp
          src/media.cpp src/entities.cpp src/coordinates.cpp
          src/bounding_box.cpp src/place_attributes.cpp src/place.cpp
          src/user.cpp src/tweet.cpp)

add_library(TAL STATIC ${TAL_SRC})

set(TEST test/messy_tester.cpp)

find_package(Boost 1.58.0 COMPONENTS system iostreams)
if(Boost_FOUND)
    add_executable(tests ${TEST})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
endif(ZLIB_FOUND)

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

# Link libraries to executables
target_link_libraries(tests TAL ${ZLIB_LIBRARIES} ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES} -pthread gtest gtest_main)

# Doxygen Target - Doxyfile in project/doc - make doc
find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
