#include <twitterlib/detail/authorize.hpp>

#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <twitterlib/app.hpp>

namespace twitter {
namespace detail {

void account_authorize(network::Request& r, const App& app) {
    network::authorize(r, app.consumer_key, app.consumer_secret,
                       app.account.token, app.account.secret);
}

void app_only_authorize(network::Request& r, App& app) {
    if (app.bearer_token.empty()) {
        app.bearer_token =
            network::get_bearer_token(app.consumer_key, app.consumer_secret);
    }
    r.authorization = "Bearer " + app.bearer_token;
}

}  // namespace detail
}  // namespace twitter
