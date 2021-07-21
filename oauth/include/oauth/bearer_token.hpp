#ifndef OAUTH_BEARER_TOKEN_HPP
#define OAUTH_BEARER_TOKEN_HPP
#include <string>
#include <string_view>

namespace oauth {

/// Get bearer token from server.
[[nodiscard]] auto get_bearer_token(std::string_view consumer_key,
                                    std::string_view consumer_secret)
    -> std::string;

}  // namespace oauth
#endif  // OAUTH_BEARER_TOKEN_HPP
