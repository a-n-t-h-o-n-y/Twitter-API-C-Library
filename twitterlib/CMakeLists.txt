cmake_minimum_required(VERSION 3.14)
project(twitterlib LANGUAGES CXX)

find_package(Boost 1.58 REQUIRED)

add_library(twitterlib STATIC
    src/detail/utility.cpp
    src/objects/bounding_box.cpp
    src/objects/coordinates.cpp
    src/objects/entities.cpp
    src/objects/hashtag.cpp
    src/objects/indices.cpp
    src/objects/media.cpp
    src/objects/place.cpp
    src/objects/size.cpp
    src/objects/sizes.cpp
    src/objects/symbol.cpp
    src/objects/tweet.cpp
    src/objects/url.cpp
    src/objects/user.cpp
    src/objects/user_mention.cpp
    src/rest/account.cpp
    src/rest/application.cpp
    src/rest/blocks.cpp
    src/rest/collections.cpp
    src/rest/favorites.cpp
    src/rest/help.cpp
    src/rest/statuses.cpp
    src/twitter_streams.cpp
)

target_include_directories(twitterlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

target_link_libraries(twitterlib
    PUBLIC
        networklib
        oauth
        Boost::boost
)

target_compile_features(twitterlib
    PUBLIC
        cxx_std_17
)

target_compile_options(networklib
    PUBLIC
        -Wall
        -Wextra
        -Wpedantic
)

install(TARGETS twitterlib EXPORT TwitterLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT TwitterLibraryConfig DESTINATION share/TwitterLibrary/cmake)
export(TARGETS twitterlib FILE TwitterLibraryConfig.cmake)
