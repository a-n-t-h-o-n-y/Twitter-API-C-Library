#ifndef TWITTERLIB_REST_API_REST_FAVORITES_HPP
#define TWITTERLIB_REST_API_REST_FAVORITES_HPP
#include <cstdint>
#include <string>
#include <vector>

#include <twitterlib/objects/tweet.hpp>

namespace twitter {
struct App;

/// Use -1 or empty string for a value you do not wish to specify.
std::vector<Tweet> get_favorites(const App& app,
                                 const std::string& screen_name,
                                 int count = -1,
                                 bool include_entities = false,
                                 std::int64_t user_id = -1,
                                 std::int64_t since_id = -1,
                                 std::int64_t max_id = -1);

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_FAVORITES_HPP
