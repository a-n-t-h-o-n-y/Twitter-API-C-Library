#ifndef OAUTH_CREDENTIALS_HPP
#define OAUTH_CREDENTIALS_HPP
#include <string>

namespace oauth {

/// OAuth Keys and Tokens
struct Credentials {
    std::string consumer_key;
    std::string consumer_secret;
    std::string user_token;
    std::string token_secret;
};

}  // namespace oauth
#endif  // OAUTH_CREDENTIALS_HPP
