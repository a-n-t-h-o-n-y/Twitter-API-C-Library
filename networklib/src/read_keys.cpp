#include <networklib/oauth/read_keys.hpp>

#include <exception>
#include <fstream>
#include <string>

namespace network {

Keys read_keys(std::string filename) {
    std::ifstream keys_stream{filename};
    Keys keys;
    if (!keys_stream) {
        return keys;
    }
    std::string disregard;
    keys_stream >> disregard;
    keys_stream >> keys.consumer_key;
    keys_stream >> disregard;
    keys_stream >> keys.consumer_secret;
    keys_stream >> disregard;
    keys_stream >> keys.user_token;
    keys_stream >> disregard;
    keys_stream >> keys.token_secret;

    if (keys.consumer_key.empty() || keys.consumer_secret.empty() ||
        keys.user_token.empty() || keys.token_secret.empty()) {
        throw std::invalid_argument("Invalid oauth tokens.");
    }
    return keys;
}

}  // namespace network
