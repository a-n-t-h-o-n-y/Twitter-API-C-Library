#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "../response.hpp"
#include "types.hpp"

#include <memory>

namespace tal {
class Request;
namespace detail {

std::unique_ptr<ssl_socket> make_connection(const Request& r);

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Response send_HTTP(const Request& request);

/// Throws exception if HTTP resonse is not 200.
void digest(const Response& response);

/// Reads a message body if it is chunked.
std::string read_chunked_body(ssl_socket& socket);

}  // namespace detail
}  // namespace tal

#endif  // NETWORK_HPP
