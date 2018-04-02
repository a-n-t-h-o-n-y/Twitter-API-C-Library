# REST API Tests
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# statuses
add_executable(statuses EXCLUDE_FROM_ALL statuses.cpp)
target_link_libraries(statuses twitterlib)
target_compile_features(statuses PUBLIC cxx_std_14)

# favorites
add_executable(favorites EXCLUDE_FROM_ALL favorites.cpp)
target_link_libraries(favorites twitterlib)
target_compile_features(favorites PUBLIC cxx_std_14)

# account
add_executable(account EXCLUDE_FROM_ALL account.cpp)
target_link_libraries(account twitterlib)
target_compile_features(account PUBLIC cxx_std_14)

# blocks
add_executable(blocks EXCLUDE_FROM_ALL blocks.cpp)
target_link_libraries(blocks twitterlib)
target_compile_features(blocks PUBLIC cxx_std_14)

# collections
add_executable(collections EXCLUDE_FROM_ALL collections.cpp)
target_link_libraries(collections twitterlib)
target_compile_features(collections PUBLIC cxx_std_14)

# application
add_executable(application EXCLUDE_FROM_ALL application.cpp)
target_link_libraries(application twitterlib)
target_compile_features(application PUBLIC cxx_std_14)

# Consolidate REST test targets
add_custom_target(rest_tests DEPENDS statuses favorites account blocks
    collections application)
