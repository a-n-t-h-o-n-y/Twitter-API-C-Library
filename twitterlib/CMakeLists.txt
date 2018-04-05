project(twitterlib LANGUAGES CXX)

add_library(twitterlib STATIC
    src/bounding_box.cpp
    src/coordinates.cpp
    src/entities.cpp
    src/hashtag.cpp
    src/media.cpp
    src/twitter_stream.cpp
    src/place.cpp
    src/place_attributes.cpp
    src/size.cpp
    src/sizes.cpp
    src/tweet.cpp
    src/url.cpp
    src/user.cpp
    src/user_mention.cpp
    src/authorize.cpp
    src/rest_account.cpp
    src/rest_favorites.cpp
    src/rest_statuses.cpp
    src/rest_blocks.cpp
    src/rest_collections.cpp
    src/rest_application.cpp
    )

target_include_directories(twitterlib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
    )

target_compile_features(twitterlib PUBLIC cxx_std_14)

# LINK LIBRARIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
target_link_libraries(twitterlib PUBLIC networklib boost)

# INSTALLATION
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
install(TARGETS twitterlib EXPORT TwitterLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT TwitterLibraryConfig DESTINATION share/TwitterLibrary/cmake)
export(TARGETS twitterlib FILE TwitterLibraryConfig.cmake)

# TESTS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# add_executable(test_twitterlib test/test_twitterlib.cpp)
# target_link_libraries(test_twitterlib twitterlib)
# add_test(test_twitterlib test_twitterlib)
