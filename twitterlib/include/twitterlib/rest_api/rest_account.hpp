#ifndef TWITTERLIB_REST_API_REST_ACCOUNT_HPP
#define TWITTERLIB_REST_API_REST_ACCOUNT_HPP
#include <networklib/response.hpp>

namespace twitter {
struct App;

auto get_account_settings(const App& app) -> network::Response;

auto verify_credentials(const App& app,
                        bool include_entities = true,
                        bool skip_status      = false,
                        bool include_email    = false) -> network::Response;

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_ACCOUNT_HPP
