#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "../response.hpp"

#include <memory>

namespace tal {
class Request;
namespace detail {

using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

std::unique_ptr<ssl_socket> make_connection(const Request& r);

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Response send_HTTP(const Request& request);

/// Throws exception if HTTP resonse is not 200.
void digest(const Response& response);

}  // namespace detail
}  // namespace tal

#endif  // NETWORK_HPP
