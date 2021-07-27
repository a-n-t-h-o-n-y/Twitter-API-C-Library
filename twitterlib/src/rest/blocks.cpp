#include <twitterlib/rest/blocks.hpp>

#include <string>
#include <vector>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/detail/utility.hpp>
#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

// Cursored Results
auto get_blocked_ids(oauth::Credentials const& keys,
                     std::optional<bool> stringify_ids)
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

        if (stringify_ids.has_value()) {
            r.queries.push_back(
                {"stringify_ids", to_string(stringify_ids.value())});
        }

        authorize(r, keys);

        auto const page = to_ptree(https_read(https_write(r)));
        for (auto const& id : page.get_child("ids"))
            result.push_back(id.second.get_value<Twitter_id>());

        cursor = page.get<std::string>("next_cursor", "0");
    }
    return result;
}

auto get_blocked_users(oauth::Credentials const& keys,
                       Get_blocked_users_parameters const& p)
    -> std::vector<User>
{
    using namespace network;

    auto result = std::vector<User>{};
    auto cursor = std::string{"-1"};
    while (cursor != "0") {
        auto r        = Request{};
        r.HTTP_method = "GET";
        r.URI         = "/1.1/blocks/list.json";

        r.queries.push_back({"cursor", cursor});

        if (p.include_entities.has_value()) {
            r.queries.push_back(
                {"include_entities", to_string(p.include_entities.value())});
        }

        if (p.skip_status.has_value()) {
            r.queries.push_back(
                {"skip_status", to_string(p.skip_status.value())});
        }

        authorize(r, keys);

        auto const page = to_ptree(https_read(https_write(r)));
        for (auto const& user : page.get_child("users"))
            result.push_back(parse_user(user.second));

        cursor = page.get<std::string>("next_cursor", "0");
    }
    return result;
}

}  // namespace twitter
