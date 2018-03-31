#ifndef NETWORKLIB_OAUTH_OAUTH_HPP
#define NETWORKLIB_OAUTH_OAUTH_HPP
#include <string>

namespace network {
class Request;

/// Add App and Account OAuth 1.0a header to HTTP request.
void authorize(Request& request,
               const std::string& consumer_key,
               const std::string& consumer_secret,
               const std::string& access_token,
               const std::string& token_secret);

/// Get bearer token from server
std::string get_bearer_token(const std::string& consumer_key,
                             const std::string& consumer_secret);

}  // namespace network
#endif  // NETWORKLIB_OAUTH_OAUTH_HPP
