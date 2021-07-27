#include <twitterlib/rest/favorites.hpp>

#include <cstdint>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/detail/types.hpp>
#include <twitterlib/detail/utility.hpp>
#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

auto get_favorites(oauth::Credentials const& keys,
                   Get_favorites_parameters const& p) -> std::vector<Tweet>
{
    using namespace network;

    auto r        = Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/favorites/list.json";

    if (p.screen_name.has_value())
        r.queries.push_back({"screen_name", p.screen_name.value()});

    if (p.user_id.has_value())
        r.queries.push_back({"user_id", to_string(p.user_id.value())});

    if (p.count.has_value())
        r.queries.push_back({"count", to_string(p.count.value())});

    if (p.since_id.has_value())
        r.queries.push_back({"since_id", to_string(p.since_id.value())});

    if (p.max_id.has_value())
        r.queries.push_back({"max_id", to_string(p.max_id.value())});

    if (p.include_entities.has_value()) {
        r.queries.push_back(
            {"include_entities", to_string(p.include_entities.value())});
    }

    // Parse Tweet Array
    authorize(r, keys);
    auto tree   = to_ptree(https_read(https_write(r)));
    tree        = tree.get_child("");
    auto result = std::vector<Tweet>{};
    for (auto const& pair : tree)
        result.push_back(parse_tweet(pair.second));

    return result;
}

}  // namespace twitter
