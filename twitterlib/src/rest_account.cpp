#include <twitterlib/rest_api/rest_account.hpp>

#include <networklib/request.hpp>
#include <networklib/send.hpp>
#include <twitterlib/app.hpp>
#include <twitterlib/detail/authorize.hpp>

namespace twitter {

network::Response get_account_settings(const App& app) {
    network::Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/account/settings.json";
    detail::account_authorize(r, app);
    return network::send(r);
}

}  // namespace twitter
