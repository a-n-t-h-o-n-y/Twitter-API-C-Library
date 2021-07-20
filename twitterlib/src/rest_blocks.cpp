#include <twitterlib/rest_api/rest_blocks.hpp>

#include <string>
#include <vector>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/oauth/credentials.hpp>
#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

// Cursored Results
auto get_blocked_ids(network::Credentials const& keys)
    -> std::vector<Twitter_id>
{
    using namespace network;
    auto result = std::vector<Twitter_id>{};
    auto cursor = std::string{"-1"};
    while (cursor != "0") {
        auto r        = Request{};
        r.HTTP_method = "GET";
        r.URI         = "/1.1/blocks/ids.json";
        r.queries.push_back({"cursor", cursor});

        authorize(r, keys);

        auto const page = to_ptree(https_read(https_write(r)));
        for (auto const& id : page.get_child("ids"))
            result.push_back(id.second.get_value<Twitter_id>());

        cursor = get(page, "next_cursor");
    }
    return result;
}

// Cursored Results
auto get_blocked_users(network::Credentials const& keys,
                       bool /*include_entities*/,
                       bool /*skip_status*/) -> std::vector<User>
{
    using namespace network;

    auto result = std::vector<User>{};
    auto cursor = std::string{"-1"};
    while (cursor != "0") {
        auto r        = Request{};
        r.HTTP_method = "GET";
        r.URI         = "/1.1/blocks/list.json";
        r.queries.push_back({"cursor", cursor});

        authorize(r, keys);

        auto const page = to_ptree(https_read(https_write(r)));
        for (auto const& user : page.get_child("users"))
            result.emplace_back(user.second);

        cursor = get(page, "next_cursor");
    }
    return result;
}

}  // namespace twitter
