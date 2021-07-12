#ifndef TWITTERLIB_REST_API_REST_APPLICATION_HPP
#define TWITTERLIB_REST_API_REST_APPLICATION_HPP
#include <networklib/response.hpp>

namespace twitter {
struct App;

auto get_application_rate_limit_status(App& app) -> network::Response;

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_APPLICATION_HPP
