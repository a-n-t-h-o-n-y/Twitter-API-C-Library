cmake_minimum_required(VERSION 3.14)
project(twitterlib LANGUAGES CXX)

find_package(Boost 1.58 REQUIRED)

add_library(twitterlib STATIC
    src/bounding_box.cpp
    src/coordinates.cpp
    src/entities.cpp
    src/hashtag.cpp
    src/media.cpp
    src/twitter_streams.cpp
    src/place.cpp
    src/place_attributes.cpp
    src/size.cpp
    src/sizes.cpp
    src/tweet.cpp
    src/url.cpp
    src/user.cpp
    src/user_mention.cpp
    src/rest_account.cpp
    src/rest_favorites.cpp
    src/rest_statuses.cpp
    src/rest_blocks.cpp
    src/rest_collections.cpp
    src/rest_application.cpp
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
