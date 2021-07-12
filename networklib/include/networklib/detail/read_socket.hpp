#ifndef NETWORKLIB_DETAIL_READ_SOCKET_HPP
#define NETWORKLIB_DETAIL_READ_SOCKET_HPP
#include <cstddef>
#include <string>

#include <networklib/detail/socket_stream.hpp>

namespace network {
namespace detail {

auto read_chunk(Socket_stream& socket, Streambuf& buffer) -> std::string;

auto read_length(Socket_stream& socket,
                        std::size_t n,
                        Streambuf& buffer) -> std::string;

}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_READ_SOCKET_HPP
