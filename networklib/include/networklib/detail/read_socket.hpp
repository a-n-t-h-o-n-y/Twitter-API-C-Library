#ifndef NETWORKLIB_DETAIL_READ_SOCKET_HPP
#define NETWORKLIB_DETAIL_READ_SOCKET_HPP
#include <cstddef>
#include <string>

#include <networklib/detail/socket_stream.hpp>
#include <networklib/socket.hpp>

namespace network::detail {

/// Read a single chunk from \p socket, using \p buffer.
/** \p buffer is a parameter because boost::read_until is used and it can leave
 *  data in the buffer. */
[[nodiscard]] auto read_chunk(Socket& socket, Streambuf& buffer) -> std::string;

/// Read \p n bytes from \p socket, using \p buffer.
/** Do not mix with read_chunk using the same buffer, it does not check for
 *  leftover bytes in the buffer before reading. */
[[nodiscard]] auto read_length(Socket& socket, Streambuf& buffer, std::size_t n)
    -> std::string;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_READ_SOCKET_HPP
