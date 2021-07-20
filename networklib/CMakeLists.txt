cmake_minimum_required(VERSION 3.14)
project(networklib LANGUAGES CXX)

# External Libraries
find_package(Boost 1.58 REQUIRED COMPONENTS system iostreams)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_library(networklib STATIC
    src/encode.cpp
    src/headers.cpp
    src/response.cpp
    src/https_read.cpp
    src/read_credentials.cpp
    src/https_write.cpp
    src/gzip.cpp
    src/oauth.cpp
    src/read_buffer.cpp
    src/read_socket.cpp
    src/socket.cpp
    src/wait.cpp
    src/request.cpp
    src/status_line.cpp
    src/stream.cpp
    src/read_credentials.cpp
    src/view_ptree.cpp
)

target_include_directories(networklib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

target_link_libraries(networklib
    PUBLIC
        Boost::boost
        Boost::system
        Boost::iostreams
        ZLIB::ZLIB
        OpenSSL::SSL
        Threads::Threads
)

target_compile_features(networklib
    PUBLIC
        cxx_std_17
)

target_compile_options(networklib
    PUBLIC
        -Wall
        -Wextra
        -Wpedantic
)

install(TARGETS networklib EXPORT NetworkLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT NetworkLibraryConfig DESTINATION share/NetworkLibrary/cmake)
export(TARGETS networklib  FILE NetworkLibraryConfig.cmake)
