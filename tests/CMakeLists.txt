add_subdirectory(rest)
add_subdirectory(streams)

add_custom_target(tests DEPENDS rest_tests stream_tests)
