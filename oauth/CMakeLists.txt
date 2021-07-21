cmake_minimum_required(VERSION 3.14)
project(oauth LANGUAGES CXX)

add_library(oauth STATIC
    src/authorize.cpp
    src/bearer_token.cpp
    src/read_credentials.cpp
)

target_include_directories(oauth
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

target_link_libraries(oauth
    PUBLIC
        networklib
)

target_compile_features(oauth
    PUBLIC
        cxx_std_17
)

target_compile_options(oauth
    PUBLIC
        -Wall
        -Wextra
        -Wpedantic
)

install(TARGETS oauth EXPORT OAuthLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT OAuthLibraryConfig DESTINATION share/OAuthLibrary/cmake)
export(TARGETS oauth  FILE OAuthLibraryConfig.cmake)
