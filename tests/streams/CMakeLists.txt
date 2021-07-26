cmake_minimum_required(VERSION 3.14)

# Sample Stream
add_executable(sample_stream EXCLUDE_FROM_ALL sample_stream.test.cpp)
target_link_libraries(sample_stream twitterlib)

# Filtered Stream
add_executable(filtered_stream EXCLUDE_FROM_ALL filtered_stream.test.cpp)
target_link_libraries(filtered_stream twitterlib)

# Consolidate REST test Targets
add_custom_target(stream_tests
    DEPENDS
        sample_stream
        filtered_stream
)
