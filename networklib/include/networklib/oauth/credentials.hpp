#ifndef NETWORKLIB_OAUTH_CREDENTIALS_HPP
#define NETWORKLIB_OAUTH_CREDENTIALS_HPP
#include <string>

namespace network {

/// OAuth Keys and Tokens
struct Credentials {
    std::string consumer_key;
    std::string consumer_secret;
    std::string user_token;
    std::string token_secret;
};

}  // namespace network
#endif  // NETWORKLIB_OAUTH_CREDENTIALS_HPP
