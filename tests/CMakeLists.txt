cmake_minimum_required(VERSION 3.14)

add_subdirectory(rest)
add_subdirectory(streams)

add_custom_target(twitterlib.tests
    DEPENDS
        rest_tests
        stream_tests
)
