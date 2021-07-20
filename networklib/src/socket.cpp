#include <networklib/socket.hpp>

#include <string>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/verify_mode.hpp>
#include <boost/system/system_error.hpp>

#include <networklib/detail/io_service.hpp>

namespace network {

auto Socket::make_connection(std::string const& host,
                             std::string const& service) -> Socket
{
    auto const endpoint_seq = [&] {
        using tcp     = boost::asio::ip::tcp;
        auto resolver = tcp::resolver{detail::io_service()};
        return resolver.resolve(host, service);
    }();

    auto socket = Socket{[] {
        namespace ssl = boost::asio::ssl;
        auto context  = ssl::context{ssl::context::sslv23};
        context.set_verify_mode(ssl::verify_peer);
        context.set_default_verify_paths();
        return context;
    }()};

    boost::asio::connect(socket.get().lowest_layer(), endpoint_seq);
    socket.get().set_verify_mode(boost::asio::ssl::verify_peer);
    socket.get().set_verify_callback(
        boost::asio::ssl::rfc2818_verification(host));
    socket.get().handshake(detail::Socket_stream::client);

    return socket;
}

auto Socket::get() -> detail::Socket_stream& { return socket_stream_; }

auto Socket::get() const -> detail::Socket_stream const&
{
    return socket_stream_;
}

void Socket::close()
{
    auto& tcp_layer = socket_stream_.lowest_layer();
    tcp_layer.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    tcp_layer.close();
}

Socket::Socket(boost::asio::ssl::context ssl_context)
    : socket_stream_{detail::io_service(), ssl_context}
{}

Socket::~Socket()
{
    if (socket_stream_.lowest_layer().is_open())
        this->close();
}

}  // namespace network
