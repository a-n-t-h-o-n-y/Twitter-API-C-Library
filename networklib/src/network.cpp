#include <networklib/detail/network.hpp>

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
#include <networklib/detail/parse.hpp>
#include <networklib/headers.hpp>
#include <networklib/message.hpp>
#include <networklib/request.hpp>

namespace tal {
namespace detail {

boost::asio::io_service& io_service() {
    static boost::asio::io_service io_s;
    return io_s;
}

std::unique_ptr<ssl_socket> make_connection(const Request& r) {
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_context.set_default_verify_paths();  // change this to certs download

    auto socket_ptr = std::make_unique<ssl_socket>(io_service(), ssl_context);

    boost::asio::ip::tcp::resolver resolver(io_service());
    boost::asio::ip::tcp::resolver::query query(r.host, r.HTTP_protocol);
    auto endpoint_iterator = resolver.resolve(query);

    // Make connection, perform tls handshake.
    boost::asio::connect(socket_ptr->lowest_layer(), endpoint_iterator);
    socket_ptr->handshake(ssl_socket::client);
    return socket_ptr;
}  // namespace detail

// This should only write to the socket the request, it should return the
// ssl_socket, and the client can use that socket to read a status_line etc..
Message send_HTTP(const Request& request) {
    auto socket_ptr = make_connection(request);
    // Send request
    boost::asio::streambuf buffer_send;
    std::ostream stream(&buffer_send);
    stream << request;
    boost::asio::write(*socket_ptr, buffer_send);

    // Read Response - throws
    boost::asio::streambuf buffer_read;
    detail::digest(Status_line(*socket_ptr, buffer_read));

    auto header = Headers(*socket_ptr, buffer_read);
    // std::cout << "headers: \n" << header << std::endl;
    std::string content_length = header.get("content-length");
    std::string message;
    if (!content_length.empty()) {
        auto length = std::stoi(content_length);
        message = detail::read_length(*socket_ptr, length, buffer_read);
    } else if (header.get("transfer-encoding") == "chunked") {
        while (true) {
            std::string chunk{read_chunk(*socket_ptr, buffer_read)};
            if (chunk.empty()) {
                break;
            }
            if (chunk != " ") {
                message.append(chunk);
            }
        }
    }
    if (header.get("content-encoding") == "gzip") {
        detail::decode_gzip(message);
    }

    socket_ptr->lowest_layer().close();
    // std::cout << message << std::endl;
    return Message(message);
}

void digest(const Status_line& status) {
    if (status.status_code != "200") {
        std::stringstream ss;
        ss << "HTTP error. Reason: ";
        ss << status.reason_phrase;
        ss << ". Status Code: ";
        ss << status.status_code;
        throw std::runtime_error(ss.str());
    }
}

}  // namespace detail
}  // namespace tal
