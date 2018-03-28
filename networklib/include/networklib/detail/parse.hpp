#ifndef NETWORKLIB_DETAIL_PARSE_HPP
#define NETWORKLIB_DETAIL_PARSE_HPP
#include <cstddef>
#include <string>

#include <boost/asio/streambuf.hpp>

#include <networklib/detail/types.hpp>

namespace network {
namespace detail {

std::string read_chunk(ssl_socket& socket, boost::asio::streambuf& buffer);

std::string read_length(ssl_socket& socket,
                        std::size_t n,
                        boost::asio::streambuf& buffer);
}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_PARSE_HPP
