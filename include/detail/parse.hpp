#ifndef PARSE_HPP
#define PARSE_HPP

#include "types.hpp"

#include <string>
#include <cstddef>

namespace tal {
namespace detail {

std::string read_chunk(ssl_socket& socket);

std::string read_length(ssl_socket& socket, std::size_t n);

} // namespace detail
} // namespace tal
#endif // PARSE_HPP
