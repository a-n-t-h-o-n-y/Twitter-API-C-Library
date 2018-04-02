#include <twitterlib/rest_api/rest_collections.hpp>

#include <string>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/send.hpp>
#include <twitterlib/app.hpp>
#include <twitterlib/detail/authorize.hpp>
#include <twitterlib/detail/to_string.hpp>

namespace twitter {

network::Response get_collection(const App& app,
                                 const std::string& id,
                                 int count,
                                 int max_position,
                                 int min_position) {
    network::Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/collections/entries.json";
    r.add_query("id", id);
    if (count != -1) {
        r.add_query("count", detail::to_string(count));
    }
    if (max_position != -1) {
        r.add_query("max_position", detail::to_string(max_position));
    }
    if (min_position != -1) {
        r.add_query("min_position", detail::to_string(min_position));
    }
    detail::account_authorize(r, app);
    return network::send(r);
}

network::Response find_collections(const App& app,
                                   const std::string& screen_name,
                                   std::int64_t user_id,
                                   std::int64_t tweet_id,
                                   int count) {
    network::Response result;
    std::string cursor{"-1"};
    // not actually cursored, you need a way to accumulate what you return
    // while (cursor != "0") {
    network::Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/collections/list.json";
    r.add_query("cursor", cursor);
    r.add_query("screen_name", screen_name);
    detail::account_authorize(r, app);
    result = network::send(r);
    cursor = result.get("response.cursors.next_cursor");
    // }
    return result;
}

network::Response get_collection_info(const App& app, const std::string& id) {
    network::Response result;
    network::Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/collections/show.json";
    r.add_query("id", id);

    detail::account_authorize(r, app);
    return network::send(r);
}

}  // namespace twitter
