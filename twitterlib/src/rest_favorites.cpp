#include <twitterlib/rest/favorites.hpp>

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/detail/to_string.hpp>
#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

auto get_favorites(oauth::Credentials const& keys,
                   std::string const& screen_name,
                   int count,
                   bool include_entities,
                   std::int64_t user_id,
                   std::int64_t since_id,
                   std::int64_t max_id) -> std::vector<Tweet>
{
    using namespace network;

    auto r        = Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/favorites/list.json";

    if (!screen_name.empty())
        r.queries.push_back({"screen_name", screen_name});

    if (count != -1)
        r.queries.push_back({"count", detail::to_string(count)});

    r.queries.push_back(
        {"include_entities", detail::to_string(include_entities)});

    if (user_id != -1)
        r.queries.push_back({"user_id", detail::to_string(user_id)});

    if (since_id != -1)
        r.queries.push_back({"since_id", detail::to_string(since_id)});

    if (max_id != -1)
        r.queries.push_back({"max_id", detail::to_string(max_id)});

    // Parse Tweet Array
    authorize(r, keys);
    auto tree   = to_ptree(https_read(https_write(r)));
    tree        = tree.get_child("");
    auto result = std::vector<Tweet>{};
    for (auto const& pair : tree)
        result.emplace_back(pair.second);

    return result;
}

}  // namespace twitter
