#ifndef TWITTERLIB_REST_API_REST_BLOCK_HPP
#define TWITTERLIB_REST_API_REST_BLOCK_HPP
#include <cstdint>
#include <vector>

#include <twitterlib/objects/user.hpp>

namespace twitter {
struct App;
using Twitter_id = std::int64_t;

auto get_blocked_ids(const App& app) -> std::vector<Twitter_id>;

auto get_blocked_users(const App& app,
                       bool include_entities = false,
                       bool skip_status      = true) -> std::vector<User>;

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_BLOCK_HPP
