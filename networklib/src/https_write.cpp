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

    // GCC 8.3 picks the copy constructor over the move constructor here.
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER) && \
    __GNUC__ < 9
    return std::move(socket);
#else
    return socket;
#endif
}

}  // namespace network
