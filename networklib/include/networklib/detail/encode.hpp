#ifndef NETWORKLIB_DETAIL_ENCODE_HPP
#define NETWORKLIB_DETAIL_ENCODE_HPP
#include <string>
#include <vector>

namespace network::detail {

/// Encodes a list of key-value pairs into a string with values URL encoded.
auto key_value_encode(
    const std::vector<std::pair<std::string, std::string>>& parameters)
    -> std::string;

/// URL/Percent encodes a given string.
auto url_encode(const std::string& text) -> std::string;

/// Base64 encoding
auto base64_encode(const std::vector<unsigned char>& message) -> std::string;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_ENCODE_HPP
