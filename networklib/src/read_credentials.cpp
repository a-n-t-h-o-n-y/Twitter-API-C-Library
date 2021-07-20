#include <networklib/oauth/read_credentials.hpp>

#include <exception>
#include <fstream>
#include <istream>
#include <stdexcept>
#include <string>

#include <networklib/oauth/credentials.hpp>

namespace network {

auto read_credentials(std::istream& stream) -> Credentials
{
    auto keys = Credentials{};
    auto pit  = std::string{};
    stream >> pit;
    stream >> keys.consumer_key;
    stream >> pit;
    stream >> keys.consumer_secret;
    stream >> pit;
    stream >> keys.user_token;
    stream >> pit;
    stream >> keys.token_secret;

    if (keys.consumer_key.empty() || keys.consumer_secret.empty() ||
        keys.user_token.empty() || keys.token_secret.empty()) {
        throw std::runtime_error("Invalid OAuth Credentials");
    }

    return keys;
}

auto read_credentials(std::string const& filename) -> Credentials
{
    auto f_stream = std::ifstream{filename};
    if (!f_stream)
        throw std::runtime_error{"read_keys: " + filename + " not found."};

    return read_credentials(f_stream);
}

}  // namespace network
