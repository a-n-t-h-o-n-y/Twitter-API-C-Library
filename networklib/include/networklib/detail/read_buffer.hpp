#ifndef NETWORKLIB_DETAIL_READ_BUFFER_HPP
#define NETWORKLIB_DETAIL_READ_BUFFER_HPP
#include <cstddef>
#include <string>

#include <networklib/detail/socket_stream.hpp>

namespace network::detail {

/// Read \p count bytes off of \p buffer and return them as a string.
[[nodiscard]] auto read_buffer(Streambuf& buffer, std::size_t count)
    -> std::string;

/// Remove all data from \p buffer
[[nodiscard]] auto flush_buffer(Streambuf& buffer) -> std::string;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_READ_BUFFER_HPP
