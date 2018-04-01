#include <twitterlib/app.hpp>

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/send.hpp>
#include <twitterlib/detail/to_string.hpp>
#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

// void App::update_status(const std::string& message) {
//     network::Request us_request;
//     us_request.HTTP_method = "POST";
//     us_request.URI = "/1.1/statuses/update.json";
//     us_request.add_message("status", message);
//     this->send(us_request, account_);
// }

// network::Response App::verify_credentials(bool include_entities,
//                                           bool skip_status,
//                                           bool include_email) {
//     network::Request r;
//     r.HTTP_method = "GET";
//     r.URI = "/1.1/account/verify_credentials.json";

//     r.add_query("include_entities", detail::to_string(include_entities));
//     r.add_query("skip_status", detail::to_string(skip_status));
//     r.add_query("include_email", detail::to_string(include_email));
//     return this->send(r, account_);
// }

// network::Response App::get_application_rate_limit_status() {
//     network::Request r;
//     r.HTTP_method = "GET";
//     r.URI = "/1.1/application/rate_limit_status.json";
//     return this->send(r);
// }

// network::Response App::get_account_rate_limit_status() {
//     network::Request r;
//     r.HTTP_method = "GET";
//     r.URI = "/1.1/application/rate_limit_status.json";
//     return this->send(r, account_);
// }

// // cursored results
// std::vector<std::int64_t> App::get_blocked_ids() {
//     std::vector<std::int64_t> result;
//     std::string cursor{"-1"};
//     while (cursor != "0") {
//         network::Request r;
//         r.HTTP_method = "GET";
//         r.URI = "/1.1/blocks/ids.json";
//         r.add_query("cursor", cursor);
//         network::Response page = this->send(r, account_);
//         for (auto& id : page.ptree().get_child("ids")) {
//             result.push_back(id.second.get_value<std::int64_t>());
//         }
//         cursor = page.get("next_cursor");
//     }
//     return result;
// }

// std::vector<User> App::get_blocked_users(bool include_entities,
//                                          bool skip_status) {
//     std::vector<User> result;
//     std::string cursor{"-1"};
//     while (cursor != "0") {
//         network::Request r;
//         r.HTTP_method = "GET";
//         r.URI = "/1.1/blocks/list.json";
//         r.add_query("cursor", cursor);
//         network::Response page = this->send(r, account_);
//         for (auto& user : page.ptree().get_child("users")) {
//             result.emplace_back(user.second);
//         }
//         cursor = page.get("next_cursor");
//     }
//     return result;
// }

// network::Response App::get_collection(const std::string& id,
//                                       int count,
//                                       int max_position,
//                                       int min_position) {
//     network::Request r;
//     r.HTTP_method = "GET";
//     r.URI = "/1.1/collections/entries.json";
//     r.add_query("id", id);
//     if (count != -1) {
//         r.add_query("count", detail::to_string(count));
//     }
//     if (max_position != -1) {
//         r.add_query("max_position", detail::to_string(max_position));
//     }
//     if (min_position != -1) {
//         r.add_query("min_position", detail::to_string(min_position));
//     }
//     return this->send(r, account_);
// }

// network::Response App::find_collections(const std::string& screen_name,
//                                         std::int64_t user_id,
//                                         std::int64_t tweet_id,
//                                         int count) {
//     network::Response result;
//     std::string cursor{"-1"};
//     // not actually cursored, you need a way to accumulate what you return
//     while (cursor != "0") {
//         network::Request r;
//         r.HTTP_method = "GET";
//         r.URI = "/1.1/collections/list.json";
//         r.add_query("cursor", cursor);
//         r.add_query("screen_name", screen_name);
//         result = this->send(r, account_);
//         cursor = result.get("response.cursors.next_cursor");
//     }
//     return result;
// }


}  // namespace twitter
