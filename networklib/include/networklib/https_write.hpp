#ifndef NETWORKLIB_HTTPS_WRITE_HPP
#define NETWORKLIB_HTTPS_WRITE_HPP
#include <networklib/socket.hpp>

namespace network {

struct Request;

/// Creates a connection to \p request's endpoint and writes \p request to it.
/** Returns the socket used to make the write so it can be passed on to read. */
[[nodiscard]] auto https_write(Request const& request) -> Socket;

}  // namespace network
#endif  // NETWORKLIB_HTTPS_WRITE_HPP
