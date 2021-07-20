#ifndef NETWORKLIB_OAUTH_OAUTH_HPP
#define NETWORKLIB_OAUTH_OAUTH_HPP
#include <string>
#include <string_view>

#include <networklib/oauth/credentials.hpp>

namespace network {
struct Request;

/// Add App and Account OAuth 1.0a header to HTTP request.
void authorize(Request& request, Credentials const& keys);

/// Get bearer token from server
[[nodiscard]] auto get_bearer_token(std::string_view consumer_key,
                                    std::string_view consumer_secret)
    -> std::string;

}  // namespace network
#endif  // NETWORKLIB_OAUTH_OAUTH_HPP
