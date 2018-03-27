#ifndef DETAIL_NETWORK_HPP
#define DETAIL_NETWORK_HPP
#include <memory>

#include <networklib/detail/types.hpp>
#include <networklib/response.hpp>
#include <networklib/status_line.hpp>

// just need to be able to forward declar boost::asio::io_service..
// Okay, can probably contain io_service to network.cpp or wherever it needs to
// be. Then these go away

namespace tal {
class Request;
namespace detail {

// boost::asio::io_service& io_service();  // try to forward declare io_service

std::unique_ptr<ssl_socket> make_connection(const Request& r);

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Response send_HTTP(const Request& request);

/// Throws exception if HTTP resonse is not 200.
void digest(const Status_line& status);

/// Reads a message body if it is chunked.
// std::string read_chunked_body(ssl_socket& socket);

}  // namespace detail
}  // namespace tal

#endif  // DETAIL_NETWORK_HPP
