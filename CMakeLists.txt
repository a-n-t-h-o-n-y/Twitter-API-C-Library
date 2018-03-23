cmake_minimum_required(VERSION 3.2)
project (TwitterLib LANGUAGES CXX)

# BUILD OPTIONS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall)

# EXTERNAL LIBRARIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
find_package(Boost 1.58.0 REQUIRED COMPONENTS system iostreams)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(Threads REQUIRED)

# PROJECT FILES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Include Directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source Files
set(TWITTER_LIB_SRC
    "src/account.cpp"
    "src/app.cpp"
    "src/oauth.cpp"
    "src/request.cpp"
    "src/encode.cpp"
    "src/network.cpp"
    "src/stream.cpp"
    "src/status_line.cpp"
    "src/headers.cpp"
    "src/message.cpp"
    "src/parse.cpp"
    "src/hashtag.cpp"
    "src/size.cpp"
    "src/sizes.cpp"
    "src/url.cpp"
    "src/user_mention.cpp"
    "src/media.cpp"
    "src/entities.cpp"
    "src/coordinates.cpp"
    "src/bounding_box.cpp"
    "src/place_attributes.cpp"
    "src/place.cpp"
    "src/user.cpp"
    "src/tweet.cpp"
    )

# TEST AND DEMOS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# enable_testing()
set(DEMO "test/main.cpp")

# EXECUTABLES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Library Target
add_library(twitterlib STATIC ${TWITTER_LIB_SRC})

# Demo Target
if (EXISTS "${CMAKE_SOURCE_DIR}/${DEMO}")
    add_executable(demo EXCLUDE_FROM_ALL ${DEMO})
    target_link_libraries(demo twitterlib ${ZLIB_LIBRARIES} ${Boost_LIBRARIES}
        ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}) # gtest gtest_main)
endif()

# Installation Info
include(GNUInstallDirs)
install(TARGETS twitterlib
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# MISCELLANEOUS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Build System Information For Clang-Tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(compile_commands ALL
	COMMAND [ -f ${CMAKE_SOURCE_DIR}/build/compile_commands.json ] &&
        mv ${CMAKE_SOURCE_DIR}/build/compile_commands.json
		${CMAKE_SOURCE_DIR}/compile_commands.json || :)

# Doxygen Target - Doxyfile in project/doc : make doc
find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
