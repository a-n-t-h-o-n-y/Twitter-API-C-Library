#ifndef ENCODE_HPP
#define ENCODE_HPP

#include <string>
#include <vector>

namespace tal {
namespace detail {

/// Encodes a list of key-value pairs into a string with values URL encoded.
std::string key_value_encode(
    const std::vector<std::pair<std::string, std::string>>& parameters);

/// URL/Percent encodes a given string.
std::string url_encode(const std::string& text);

/// Base64 encoding
std::string base64_encode(const std::vector<unsigned char>& message);

}  // detail
}  // namespace tal

#endif  // ENCODE_HPP
