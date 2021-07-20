#ifndef NETWORKLIB_HTTPS_READ_HPP
#define NETWORKLIB_HTTPS_READ_HPP
#include <networklib/response.hpp>
#include <networklib/socket.hpp>

namespace network {

/// Reads a Reponse from \p socket.
/** \p socket should come from a call to `https_write(Request)`. */
[[nodiscard]] auto https_read(Socket socket) -> Response;

}  // namespace network
#endif  // NETWORKLIB_HTTPS_READ_HPP
