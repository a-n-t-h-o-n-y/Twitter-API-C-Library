cmake_minimum_required(VERSION 3.14)

# Statuses
add_executable(statuses EXCLUDE_FROM_ALL statuses.test.cpp)
target_link_libraries(statuses twitterlib)

# Favorites
add_executable(favorites EXCLUDE_FROM_ALL favorites.test.cpp)
target_link_libraries(favorites twitterlib)

# Account
add_executable(account EXCLUDE_FROM_ALL account.test.cpp)
target_link_libraries(account twitterlib)

# Blocks
add_executable(blocks EXCLUDE_FROM_ALL blocks.test.cpp)
target_link_libraries(blocks twitterlib)

# Collections
add_executable(collections EXCLUDE_FROM_ALL collections.test.cpp)
target_link_libraries(collections twitterlib)

# Application
add_executable(application EXCLUDE_FROM_ALL application.test.cpp)
target_link_libraries(application twitterlib)

# Consolidate REST test targets
add_custom_target(rest_tests
    DEPENDS
        statuses
        favorites
        account
        blocks
        collections
        application
)
