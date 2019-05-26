project(networklib LANGUAGES CXX)

add_library(networklib STATIC
    src/encode.cpp
    src/headers.cpp
    src/response.cpp
    src/make_connection.cpp
    src/send.cpp
    src/gzip.cpp
    src/oauth.cpp
    src/read_socket.cpp
    src/wait.cpp
    src/request.cpp
    src/status_line.cpp
    src/stream.cpp
    src/read_keys.cpp
    src/view_ptree.cpp
    )

target_include_directories(networklib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
    )

target_compile_features(networklib PUBLIC cxx_std_14)

# EXTERNAL LIBRARIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
find_package(ZLIB REQUIRED)
add_library(zlib INTERFACE IMPORTED)
set_property(TARGET zlib PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIRS})
set_property(TARGET zlib PROPERTY
    INTERFACE_LINK_LIBRARIES ${ZLIB_LIBRARIES})

find_package(OpenSSL REQUIRED)
add_library(openssl INTERFACE IMPORTED)
set_property(TARGET openssl PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR})
set_property(TARGET openssl PROPERTY
    INTERFACE_LINK_LIBRARIES ${OPENSSL_LIBRARIES})

find_package(Threads REQUIRED)
add_library(threads INTERFACE IMPORTED)
set_property(TARGET threads PROPERTY
    INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

# LINK LIBRARIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
target_link_libraries(networklib PUBLIC boost zlib openssl threads)

# INSTALLATION
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
install(TARGETS networklib EXPORT NetworkLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT NetworkLibraryConfig DESTINATION share/NetworkLibrary/cmake)
export(TARGETS networklib  FILE NetworkLibraryConfig.cmake)

# TESTS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# add_executable(test_networklib test/test_networklib.cpp)
# target_link_libraries(test_networklib networklib)
# add_test(test_networklib test_networklib)
