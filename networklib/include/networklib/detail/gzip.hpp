#ifndef NETWORKLIB_DETAIL_GZIP_HPP
#define NETWORKLIB_DETAIL_GZIP_HPP
#include <string>
#include <string_view>

namespace network::detail {

/// Decode gzip string.
[[nodiscard]] auto decode_gzip(std::string_view zipped) -> std::string;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_GZIP_HPP
