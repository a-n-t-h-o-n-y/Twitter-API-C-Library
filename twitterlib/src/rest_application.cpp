#include <twitterlib/rest_api/rest_application.hpp>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/send.hpp>
#include <twitterlib/detail/authorize.hpp>

namespace twitter {

network::Response get_application_rate_limit_status(App& app) {
    network::Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/application/rate_limit_status.json";
    detail::app_only_authorize(r, app);
    return network::send(r);
}

}  // namespace twitter
