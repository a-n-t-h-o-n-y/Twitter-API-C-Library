#ifndef TWITTERLIB_REST_BLOCK_HPP
#define TWITTERLIB_REST_BLOCK_HPP
#include <cstdint>
#include <optional>
#include <vector>

#include <oauth/credentials.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

using Twitter_id = std::int64_t;

/// Return a list of user IDs the authenticated user is blocking.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/mute-block-report-users/api-reference/get-blocks-ids */
[[nodiscard]] auto get_blocked_ids(oauth::Credentials const& keys,
                                   std::optional<bool> stringify_ids =
                                       std::nullopt) -> std::vector<Twitter_id>;

struct Get_blocked_users_parameters {
    std::optional<bool> include_entities = std::nullopt;
    std::optional<bool> skip_status      = std::nullopt;
};

/// Get a list of Users the authenticated user is blocking.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/mute-block-report-users/api-reference/get-blocks-list */
[[nodiscard]] auto get_blocked_users(oauth::Credentials const& keys,
                                     Get_blocked_users_parameters const& p = {})
    -> std::vector<User>;

// TODO
// POST blocks/create
// POST blocks/destroy
// GET mutes/users/ids
// GET mutes/users/list
// POST mutes/users/create
// POST mutes/users/destroy
// POST users/report_spam

}  // namespace twitter
#endif  // TWITTERLIB_REST_BLOCK_HPP
