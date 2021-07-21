#ifndef TWITTERLIB_REST_FAVORITES_HPP
#define TWITTERLIB_REST_FAVORITES_HPP
#include <cstdint>
#include <string>
#include <vector>

#include <oauth/credentials.hpp>
#include <twitterlib/objects/tweet.hpp>

namespace twitter {

/// Use -1 or empty string for a value you do not wish to specify.
[[nodiscard]] auto get_favorites(oauth::Credentials const& keys,
                                 std::string const& screen_name,
                                 int count             = -1,
                                 bool include_entities = false,
                                 std::int64_t user_id  = -1,
                                 std::int64_t since_id = -1,
                                 std::int64_t max_id   = -1)
    -> std::vector<Tweet>;

}  // namespace twitter
#endif  // TWITTERLIB_REST_FAVORITES_HPP
