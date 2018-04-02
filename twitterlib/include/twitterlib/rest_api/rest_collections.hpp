#ifndef TWITTERLIB_REST_API_REST_COLLECTIONS_HPP
#define TWITTERLIB_REST_API_REST_COLLECTIONS_HPP
#include <cstdint>
#include <string>

#include <networklib/response.hpp>

namespace twitter {
struct App;

// TODO: Change return type to Colletion, that wraps a vector<Tweet> and
// includes the description data as well.
network::Response get_collection(const App& app,
                                 const std::string& id,
                                 int count = -1,
                                 int max_position = -1,
                                 int min_position = -1);

network::Response find_collections(const App& app,
                                   const std::string& screen_name,
                                   std::int64_t user_id = -1,
                                   std::int64_t tweet_id = -1,
                                   int count = -1);

network::Response get_collection_info(const App& app, const std::string& id);

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_COLLECTIONS_HPP
