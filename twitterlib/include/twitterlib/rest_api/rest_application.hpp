#ifndef TWITTERLIB_REST_API_REST_APPLICATION_HPP
#define TWITTERLIB_REST_API_REST_APPLICATION_HPP
#include <string>

#include <networklib/response.hpp>

namespace twitter {

[[nodiscard]] auto get_application_rate_limit_status(
    std::string const& bearer_token) -> network::Response;

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_APPLICATION_HPP
