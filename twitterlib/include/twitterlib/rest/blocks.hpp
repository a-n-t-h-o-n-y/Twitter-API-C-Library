#ifndef TWITTERLIB_REST_BLOCK_HPP
#define TWITTERLIB_REST_BLOCK_HPP
#include <cstdint>
#include <vector>

#include <oauth/credentials.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

using Twitter_id = std::int64_t;

[[nodiscard]] auto get_blocked_ids(oauth::Credentials const& keys)
    -> std::vector<Twitter_id>;

[[nodiscard]] auto get_blocked_users(oauth::Credentials const& keys,
                                     bool include_entities = false,
                                     bool skip_status      = true)
    -> std::vector<User>;

}  // namespace twitter
#endif  // TWITTERLIB_REST_BLOCK_HPP
