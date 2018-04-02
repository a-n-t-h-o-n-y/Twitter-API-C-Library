#include <networklib/detail/make_connection.hpp>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <networklib/detail/encode.hpp>
#include <networklib/detail/headers.hpp>
#include <networklib/detail/read_socket.hpp>
#include <networklib/detail/socket_stream.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>

namespace {

boost::asio::io_service& io_service() {
    static boost::asio::io_service io_s;
    return io_s;
}

}  // namespace

namespace network {
namespace detail {

std::unique_ptr<Socket_stream> make_connection(const Request& r) {
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_context.set_default_verify_paths();

    auto socket_ptr =
        std::make_unique<Socket_stream>(io_service(), ssl_context);

    boost::asio::ip::tcp::resolver resolver(io_service());
    boost::asio::ip::tcp::resolver::query query(r.host, r.HTTP_protocol);
    auto endpoint_iterator = resolver.resolve(query);

    // Make connection, perform tls handshake.
    boost::asio::connect(socket_ptr->lowest_layer(), endpoint_iterator);
    socket_ptr->set_verify_mode(boost::asio::ssl::verify_peer);
    socket_ptr->set_verify_callback(
        boost::asio::ssl::rfc2818_verification(r.host));
    socket_ptr->handshake(Socket_stream::client);
    return socket_ptr;
}

void wait_() {
    io_service().run();
}

}  // namespace detail
}  // namespace network
