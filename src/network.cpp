#include "detail/network.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <string>

#include "request.hpp"

namespace tal {
namespace detail {

std::unique_ptr<ssl_socket> make_connection(const Request& r) {
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_context.set_default_verify_paths();  // change this to certs download

    static boost::asio::io_service ios;  // put this in static class method

    auto socket_ptr = std::make_unique<ssl_socket>(ios, ssl_context);

    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::query query(r.host, r.HTTP_protocol);
    auto endpoint_iterator = resolver.resolve(query);

    // Make connection, perform tls handshake.
    boost::asio::connect(socket_ptr->lowest_layer(), endpoint_iterator);
    socket_ptr->handshake(ssl_socket::client);
    return socket_ptr;
}

Response send_HTTP(const Request& request) {
    auto socket_ptr = make_connection(request);
    // Send request
    boost::asio::streambuf request_buffer;
    std::ostream request_stream(&request_buffer);
    request_stream << request;
    boost::asio::write(*socket_ptr, request_buffer);

    // Read Response
    Response response{*socket_ptr};
    socket_ptr->lowest_layer().close();
    return response;
}

void digest(const Response& response) {
    if (response.status_code != "200") {
        throw std::runtime_error("HTTP error. Reason: " +
                                 response.reason_phrase + ". Status Code: " +
                                 response.status_code);
    }
}

std::string read_chunked_body(ssl_socket& socket) {
    std::string message_body;
    boost::asio::streambuf response_buffer;
    boost::system::error_code ec;
    while (true) {
        boost::asio::read_until(socket, response_buffer, "\r\n", ec);
        if (ec && ec != boost::asio::error::eof) {
            throw boost::system::system_error(ec);
        }
        std::istream response_stream(&response_buffer);
        std::string chunk_size_str;  // second time around this is '\r'
        std::getline(response_stream, chunk_size_str);
        auto chunk_size = std::stoul(chunk_size_str, nullptr, 16);
        if (chunk_size == 0) {
            auto t =
                boost::asio::read_until(socket, response_buffer, "\r\n", ec);
            std::string trash(t, ' ');
            response_stream.read(&trash[0], t);
            if (ec && ec != boost::asio::error::eof) {
                throw boost::system::system_error(ec);
            }
            break;
        }
        auto n =
            boost::asio::read(socket, response_buffer,
                              boost::asio::transfer_exactly(chunk_size), ec);
        if (ec && ec != boost::asio::error::eof) {
            throw boost::system::system_error(ec);
        }
        std::string chunk(n, ' ');
        response_stream.read(&chunk[0], n);
        message_body.append(chunk);
        auto t = boost::asio::read_until(socket, response_buffer, "\r\n", ec);
        std::string trash(t, ' ');
        response_stream.read(&trash[0], t);
        if (ec && ec != boost::asio::error::eof) {
            throw boost::system::system_error(ec);
        }
    }
    return message_body;
}

}  // namespace detail
}  // namespace tal
