#ifndef NETWORKLIB_DETAIL_ENCODE_HPP
#define NETWORKLIB_DETAIL_ENCODE_HPP
#include <string>
#include <vector>

namespace network {
namespace detail {

/// Encodes a list of key-value pairs into a string with values URL encoded.
std::string key_value_encode(
    const std::vector<std::pair<std::string, std::string>>& parameters);

/// URL/Percent encodes a given string.
std::string url_encode(const std::string& text);

/// Base64 encoding
std::string base64_encode(const std::vector<unsigned char>& message);

}  // namespace detail
}  // namespace network

#endif  // NETWORKLIB_DETAIL_ENCODE_HPP
