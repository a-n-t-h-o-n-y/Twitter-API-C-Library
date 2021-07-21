#ifndef TWITTERLIB_REST_ACCOUNT_HPP
#define TWITTERLIB_REST_ACCOUNT_HPP
#include <networklib/response.hpp>
#include <oauth/credentials.hpp>

namespace twitter {

[[nodiscard]] auto get_account_settings(oauth::Credentials const& keys)
    -> network::Response;

[[nodiscard]] auto verify_credentials(oauth::Credentials const& keys,
                                      bool include_entities = true,
                                      bool skip_status      = false,
                                      bool include_email    = false)
    -> network::Response;

}  // namespace twitter
#endif  // TWITTERLIB_REST_ACCOUNT_HPP
