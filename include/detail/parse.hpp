#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <cstddef>
#include <boost/asio/streambuf.hpp>
#include "types.hpp"

namespace tal {
namespace detail {

std::string read_chunk(ssl_socket& socket, boost::asio::streambuf& buffer);

std::string read_length(ssl_socket& socket,
                        boost::asio::streambuf& buffer,
                        std::size_t n);

}  // namespace detail
}  // namespace tal
#endif  // PARSE_HPP
