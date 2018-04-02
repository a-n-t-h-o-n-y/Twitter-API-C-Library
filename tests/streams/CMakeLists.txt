# User Stream
add_executable(user_stream EXCLUDE_FROM_ALL user_stream_test.cpp)
target_link_libraries(user_stream twitterlib)
target_compile_features(user_stream PUBLIC cxx_std_14)

# Sample Stream
add_executable(sample_stream EXCLUDE_FROM_ALL sample_stream_test.cpp)
target_link_libraries(sample_stream twitterlib)
target_compile_features(sample_stream PUBLIC cxx_std_14)

# Filtered Stream
add_executable(filtered_stream EXCLUDE_FROM_ALL filtered_stream_test.cpp)
target_link_libraries(filtered_stream twitterlib)
target_compile_features(filtered_stream PUBLIC cxx_std_14)

# Consolidate REST test Targets
add_custom_target(stream_tests DEPENDS user_stream sample_stream
    filtered_stream)
