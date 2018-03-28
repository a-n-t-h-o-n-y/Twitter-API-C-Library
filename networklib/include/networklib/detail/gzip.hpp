#ifndef NETWORKLIB_DETAIL_GZIP_HPP
#define NETWORKLIB_DETAIL_GZIP_HPP
#include <string>

namespace network {
namespace detail {

/// Decode gzip
void decode_gzip(std::string& zipped);

}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_GZIP_HPP
