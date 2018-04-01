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
