# Demos
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Twitter Search Demo
add_executable(search EXCLUDE_FROM_ALL src/search.cpp)
target_link_libraries(search twitterlib)
target_compile_features(search PUBLIC cxx_std_14)

# Get Favorites Demo
add_executable(get_favorites EXCLUDE_FROM_ALL src/get_favorites.cpp)
target_link_libraries(get_favorites twitterlib)
target_compile_features(get_favorites PUBLIC cxx_std_14)

# Consolidate Demos Targets
add_custom_target(demos DEPENDS search get_favorites)

# Verify readme examples
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_executable(readme EXCLUDE_FROM_ALL src/readme.cpp)
target_link_libraries(readme twitterlib)
target_compile_features(readme PUBLIC cxx_std_14)
