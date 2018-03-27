# Define Source files
set(DEMO_SOURCE src/main.cpp)


# Create Executable
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${DEMO_SOURCE}")
    add_executable(demo EXCLUDE_FROM_ALL ${DEMO_SOURCE})
    target_link_libraries(demo twitterlib)
    target_compile_features(demo PUBLIC cxx_std_14)
endif()

