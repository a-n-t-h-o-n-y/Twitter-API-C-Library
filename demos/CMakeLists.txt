# Twitter Search Demo
add_executable(search EXCLUDE_FROM_ALL src/search.cpp)
target_link_libraries(search twitterlib)
target_compile_features(search PUBLIC cxx_std_14)

# Consolidated Demos Target
add_custom_target(demos DEPENDS search)
