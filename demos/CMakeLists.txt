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

# REST API Tests
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# rest_statuses
add_executable(rest_statuses EXCLUDE_FROM_ALL src/rest_test/statuses.cpp)
target_link_libraries(rest_statuses twitterlib)
target_compile_features(rest_statuses PUBLIC cxx_std_14)

# rest_favorites
add_executable(rest_favorites EXCLUDE_FROM_ALL src/rest_test/favorites.cpp)
target_link_libraries(rest_favorites twitterlib)
target_compile_features(rest_favorites PUBLIC cxx_std_14)

# rest_account
add_executable(rest_account EXCLUDE_FROM_ALL src/rest_test/account.cpp)
target_link_libraries(rest_account twitterlib)
target_compile_features(rest_account PUBLIC cxx_std_14)

# rest_blocks
add_executable(rest_blocks EXCLUDE_FROM_ALL src/rest_test/blocks.cpp)
target_link_libraries(rest_blocks twitterlib)
target_compile_features(rest_blocks PUBLIC cxx_std_14)

# rest_collections
add_executable(rest_collections EXCLUDE_FROM_ALL src/rest_test/collections.cpp)
target_link_libraries(rest_collections twitterlib)
target_compile_features(rest_collections PUBLIC cxx_std_14)

# rest_application
add_executable(rest_application EXCLUDE_FROM_ALL src/rest_test/application.cpp)
target_link_libraries(rest_application twitterlib)
target_compile_features(rest_application PUBLIC cxx_std_14)

# Consolidate REST test Targets
add_custom_target(rest_test DEPENDS rest_statuses rest_favorites rest_account
    rest_blocks rest_collections rest_application)

# Verify readme examples
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_executable(readme EXCLUDE_FROM_ALL src/readme.cpp)
target_link_libraries(readme twitterlib)
target_compile_features(readme PUBLIC cxx_std_14)
