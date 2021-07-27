#ifndef TWITTERLIB_REST_FAVORITES_HPP
#define TWITTERLIB_REST_FAVORITES_HPP
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <oauth/credentials.hpp>
#include <twitterlib/detail/types.hpp>
#include <twitterlib/objects/tweet.hpp>

namespace twitter {

struct Get_favorites_parameters {
    std::optional<std::string> screen_name = std::nullopt;
    std::optional<std::int64_t> user_id    = std::nullopt;
    std::optional<Count> count             = std::nullopt;
    std::optional<std::int64_t> since_id   = std::nullopt;
    std::optional<std::int64_t> max_id     = std::nullopt;
    std::optional<bool> include_entities   = std::nullopt;
};

/// Return a list of Favorited Tweets of the given \p screen_name.
/** https://developer.twitter.com/en/docs/twitter-api/v1/tweets/post-and-engage/api-reference/get-favorites-list */
[[nodiscard]] auto get_favorites(oauth::Credentials const& keys,
                                 Get_favorites_parameters const& p)
    -> std::vector<Tweet>;

// TODO
// POST favorites/create
// POST favorites/destroy

}  // namespace twitter
#endif  // TWITTERLIB_REST_FAVORITES_HPP
