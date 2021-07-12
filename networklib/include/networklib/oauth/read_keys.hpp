#ifndef NETWORKLIB_OAUTH_READ_KEYS_HPP
#define NETWORKLIB_OAUTH_READ_KEYS_HPP
#include <string>

namespace network {

struct Keys {
    std::string consumer_key;
    std::string consumer_secret;
    std::string user_token;
    std::string token_secret;
};

auto read_keys(std::string filename) -> Keys;

}  // namespace network
#endif  // NETWORKLIB_OAUTH_READ_KEYS_HPP
