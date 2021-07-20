#include <networklib/https_write.hpp>

#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>

#include <networklib/request.hpp>
#include <networklib/socket.hpp>

namespace network {

auto https_write(Request const& request) -> Socket
{
    // Make Connection
    auto socket = Socket::make_connection(request.host, request.HTTP_protocol);

    // Send Request
    boost::asio::write(socket.get(), boost::asio::buffer(to_string(request)));

    return socket;
}

}  // namespace network
