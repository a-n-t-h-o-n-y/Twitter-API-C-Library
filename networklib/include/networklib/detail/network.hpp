#ifndef NETWORKLIB_DETAIL_NETWORK_HPP
#define NETWORKLIB_DETAIL_NETWORK_HPP
#include <memory>

#include <networklib/detail/socket_stream.hpp>
#include <networklib/detail/status_line.hpp>
#include <networklib/response.hpp>

namespace network {
class Request;
namespace detail {

std::unique_ptr<Socket_stream> make_connection(const Request& r);

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Response send_HTTP(const Request& request);

/// Throws exception if HTTP resonse is not 200.
void digest(const Status_line& status);

}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_NETWORK_HPP
