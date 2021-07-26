cmake_minimum_required(VERSION 3.14)

# Twitter Search Demo
add_executable(search EXCLUDE_FROM_ALL src/search.demo.cpp)
target_link_libraries(search twitterlib)

# Get Favorites Demo
add_executable(get_favorites EXCLUDE_FROM_ALL src/get_favorites.demo.cpp)
target_link_libraries(get_favorites twitterlib)

# Verify README examples
add_executable(readme EXCLUDE_FROM_ALL src/readme.demo.cpp)
target_link_libraries(readme twitterlib)

# Consolidate Demos Targets
add_custom_target(twitterlib.demos
    DEPENDS
        search
        get_favorites
        readme
)
