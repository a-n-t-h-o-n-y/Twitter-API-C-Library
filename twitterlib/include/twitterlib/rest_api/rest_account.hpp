#ifndef TWITTERLIB_REST_API_REST_ACCOUNT_HPP
#define TWITTERLIB_REST_API_REST_ACCOUNT_HPP
#include <networklib/oauth/credentials.hpp>
#include <networklib/response.hpp>

namespace twitter {

[[nodiscard]] auto get_account_settings(network::Credentials const& keys)
    -> network::Response;

[[nodiscard]] auto verify_credentials(network::Credentials const& keys,
                                      bool include_entities = true,
                                      bool skip_status      = false,
                                      bool include_email    = false)
    -> network::Response;

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_ACCOUNT_HPP
