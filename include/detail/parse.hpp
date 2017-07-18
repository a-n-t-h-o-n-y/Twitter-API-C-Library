#ifndef DETAIL_PARSE_HPP
#define DETAIL_PARSE_HPP

#include <string>
#include <cstddef>
#include <boost/asio/streambuf.hpp>
#include "types.hpp"

namespace tal {
namespace detail {

std::string read_chunk(ssl_socket& socket, boost::asio::streambuf& buffer);

std::string read_length(ssl_socket& socket,
                        std::size_t n,
                        boost::asio::streambuf& buffer);
}  // namespace detail
}  // namespace tal
#endif  // DETAIL_PARSE_HPP
