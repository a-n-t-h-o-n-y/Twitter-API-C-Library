#ifndef NETWORKLIB_DETAIL_ENCODE_HPP
#define NETWORKLIB_DETAIL_ENCODE_HPP
#include <string>
#include <string_view>
#include <vector>

namespace network::detail {

/// Encodes a list of key-value pairs into a string with values URL encoded.
[[nodiscard]] auto key_value_encode(
    std::vector<std::pair<std::string, std::string>> const& parameters)
    -> std::string;

/// URL/Percent encodes a given string.
[[nodiscard]] auto url_encode(std::string_view text) -> std::string;

/// Base64 encoding
[[nodiscard]] auto base64_encode(std::vector<unsigned char> const& message)
    -> std::string;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_ENCODE_HPP
