#include <twitterlib/rest_api/rest_favorites.hpp>

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/send.hpp>
#include <twitterlib/detail/authorize.hpp>
#include <twitterlib/detail/to_string.hpp>
#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

std::vector<Tweet> get_favorites(const App& app,
                                 const std::string& screen_name,
                                 int count,
                                 bool include_entities,
                                 std::int64_t user_id,
                                 std::int64_t since_id,
                                 std::int64_t max_id) {
    network::Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/favorites/list.json";

    if (!screen_name.empty()) {
        r.add_query("screen_name", screen_name);
    }
    if (count != -1) {
        r.add_query("count", detail::to_string(count));
    }
    r.add_query("include_entities", detail::to_string(include_entities));
    if (user_id != -1) {
        r.add_query("user_id", detail::to_string(user_id));
    }
    if (since_id != -1) {
        r.add_query("since_id", detail::to_string(since_id));
    }
    if (since_id != -1) {
        r.add_query("max_id", detail::to_string(max_id));
    }

    // Parse Tweet Array
    boost::property_tree::ptree tree;
    detail::account_authorize(r, app);
    network::Response response{network::send(r)};
    std::stringstream json_stream{response.json()};
    boost::property_tree::read_json(json_stream, tree);
    tree = tree.get_child("");
    std::vector<Tweet> result;
    for (const auto& pair : tree) {
        result.emplace_back(pair.second);
    }
    return result;
}

}  // namespace twitter
