#ifndef DETAIL_NETWORK_HPP
#define DETAIL_NETWORK_HPP

#include "types.hpp"
#include "message.hpp"
#include "status_line.hpp"

#include <memory>

namespace tal {
class Request;
namespace detail {

std::unique_ptr<ssl_socket> make_connection(const Request& r,
                                            boost::asio::io_service& ios);

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Message send_HTTP(const Request& request, boost::asio::io_service& ios);

/// Throws exception if HTTP resonse is not 200.
void digest(const Status_line& status);

/// Reads a message body if it is chunked.
// std::string read_chunked_body(ssl_socket& socket);

}  // namespace detail
}  // namespace tal

#endif  // DETAIL_NETWORK_HPP
