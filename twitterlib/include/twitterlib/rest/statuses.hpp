#ifndef TWITTERLIB_REST_STATUSES_HPP
#define TWITTERLIB_REST_STATUSES_HPP
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <networklib/response.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/objects/coordinates.hpp>

namespace twitter {

struct Update_status_parameters {
    std::string message;
    std::optional<std::int64_t> in_reply_to_status_id = std::nullopt;
    std::optional<bool> auto_populate_reply_metadata  = std::nullopt;
    std::vector<std::int64_t> exclude_reply_user_ids  = {};
    std::optional<std::string> attachment_url         = std::nullopt;
    std::vector<std::int64_t> media_ids               = {};
    std::optional<bool> possibly_sensitive            = std::nullopt;
    std::optional<Earth_coordinates> lat_and_long     = std::nullopt;
    std::optional<std::string> place_id               = std::nullopt;
    std::optional<bool> display_coordinates           = std::nullopt;
    std::optional<bool> trim_user                     = std::nullopt;
    std::optional<bool> enable_dmcommands             = std::nullopt;
    std::optional<bool> fail_dmcommands               = std::nullopt;
    std::optional<std::string> card_uri               = std::nullopt;
};

/// Post a new status as the authenticated user.
/** https://developer.twitter.com/en/docs/twitter-api/v1/tweets/post-and-engage/api-reference/post-statuses-update */
auto update_status(oauth::Credentials const& keys,
                   Update_status_parameters const& p) -> network::Response;

// TODO
// POST statuses/destroy/:id
// GET statuses/show/:id
// GET statuses/oembed
// GET statuses/lookup
// POST statuses/retweet/:id
// POST statuses/unretweet/:id
// GET statuses/retweets/:id
// GET statuses/retweets_of_me
// GET statuses/retweeters/ids

}  // namespace twitter
#endif  // TWITTERLIB_REST_STATUSES_HPP
