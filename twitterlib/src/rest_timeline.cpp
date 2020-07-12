#include <twitterlib/rest_api/rest_timeline.hpp>
#include <networklib/request.hpp>
#include <networklib/send.hpp>
#include <twitterlib/app.hpp>
#include <twitterlib/detail/authorize.hpp>

namespace twitter {
    network::Response get_timeline(const App &app) {
        network::Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/statuses/home_timeline.json";
        detail::account_authorize(r, app);
        return network::send(r);


    }

    network::Response get_timeline(const App &app, std::string &id) {
        network::Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/statuses/home_timeline.json";
        r.add_query("since_id", id);
        detail::account_authorize(r, app);
        return network::send(r);


    }
}
