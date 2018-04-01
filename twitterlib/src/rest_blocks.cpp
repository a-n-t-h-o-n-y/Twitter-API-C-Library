#include <twitterlib/rest_api/rest_blocks.hpp>

#include <string>
#include <vector>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/send.hpp>
#include <twitterlib/app.hpp>
#include <twitterlib/detail/authorize.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

// Cursored Results
std::vector<Twitter_id> get_blocked_ids(const App& app) {
    std::vector<Twitter_id> result;
    std::string cursor{"-1"};
    while (cursor != "0") {
        network::Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/blocks/ids.json";
        r.add_query("cursor", cursor);
        detail::account_authorize(r, app);
        network::Response page{network::send(r)};
        for (auto& id : page.ptree().get_child("ids")) {
            result.push_back(id.second.get_value<Twitter_id>());
        }
        cursor = page.get("next_cursor");
    }
    return result;
}

// Cursored Results
std::vector<User> get_blocked_users(const App& app,
                                    bool include_entities,
                                    bool skip_status) {
    std::vector<User> result;
    std::string cursor{"-1"};
    while (cursor != "0") {
        network::Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/blocks/list.json";
        r.add_query("cursor", cursor);
        detail::account_authorize(r, app);
        network::Response page{network::send(r)};
        for (auto& user : page.ptree().get_child("users")) {
            result.emplace_back(user.second);
        }
        cursor = page.get("next_cursor");
    }
    return result;
}

}  // namespace twitter
