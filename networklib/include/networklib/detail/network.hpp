#ifndef DETAIL_NETWORK_HPP
#define DETAIL_NETWORK_HPP
#include <memory>

#include <boost/asio.hpp>

#include <networklib/detail/types.hpp>
#include <networklib/message.hpp>
#include <networklib/status_line.hpp>

namespace tal {
class Request;
namespace detail {

boost::asio::io_service& io_service();  // try to forward declare io_service

std::unique_ptr<ssl_socket> make_connection(const Request& r,
                                            boost::asio::io_service& ios);

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Message send_HTTP(const Request& request);

/// Throws exception if HTTP resonse is not 200.
void digest(const Status_line& status);

/// Reads a message body if it is chunked.
// std::string read_chunked_body(ssl_socket& socket);

}  // namespace detail
}  // namespace tal

#endif  // DETAIL_NETWORK_HPP
