#include <twitterlib/rest_api/rest_account.hpp>

#include <networklib/request.hpp>
#include <networklib/send.hpp>
#include <twitterlib/app.hpp>
#include <twitterlib/detail/authorize.hpp>
#include <twitterlib/detail/to_string.hpp>

namespace twitter {

network::Response get_account_settings(const App& app) {
    network::Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/account/settings.json";
    detail::account_authorize(r, app);
    return network::send(r);
}

network::Response verify_credentials(const App& app,
                                     bool include_entities,
                                     bool skip_status,
                                     bool include_email) {
    network::Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/account/verify_credentials.json";

    r.add_query("include_entities", detail::to_string(include_entities));
    r.add_query("skip_status", detail::to_string(skip_status));
    r.add_query("include_email", detail::to_string(include_email));
    detail::account_authorize(r, app);
    return network::send(r);
}

}  // namespace twitter
