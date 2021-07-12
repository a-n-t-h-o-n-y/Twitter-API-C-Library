cmake_minimum_required(VERSION 3.14)

# User Stream
add_executable(user_stream EXCLUDE_FROM_ALL user_stream_test.cpp)
target_link_libraries(user_stream twitterlib)

# Sample Stream
add_executable(sample_stream EXCLUDE_FROM_ALL sample_stream_test.cpp)
target_link_libraries(sample_stream twitterlib)

# Filtered Stream
add_executable(filtered_stream EXCLUDE_FROM_ALL filtered_stream_test.cpp)
target_link_libraries(filtered_stream twitterlib)

# Consolidate REST test Targets
add_custom_target(stream_tests
    DEPENDS
        user_stream
        sample_stream
        filtered_stream
)
