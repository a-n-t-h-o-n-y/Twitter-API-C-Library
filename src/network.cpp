#include "detail/network.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <stdexcept>

#include "request.hpp"

namespace tal {
namespace detail {

Response send_HTTP(const Request& request) {
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_context.set_default_verify_paths();  // change this to certs download

    boost::asio::io_service ios;  // put this in static class method

    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket(
        ios, ssl_context);
    auto& lowest_layer_socket = ssl_socket.lowest_layer();

    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::query query(request.host,
                                                request.HTTP_protocol);
    auto endpoint_iterator = resolver.resolve(query);

    // Make connection, perform tls handshake.
    boost::asio::connect(lowest_layer_socket, endpoint_iterator);
    ssl_socket.handshake(
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client);

    // Send request
    boost::asio::streambuf request_buffer;
    std::ostream request_stream(&request_buffer);
    request_stream << request;
    boost::asio::write(ssl_socket, request_buffer);

    // Get Status Line Response
    Response response;
    boost::asio::streambuf response_buffer;
    boost::system::error_code ec;
    boost::asio::read_until(ssl_socket, response_buffer, "/r/n", ec);
    std::istream response_stream(&response_buffer);

    std::string http_version;
    response_stream >> http_version;
    response.HTTP_version = http_version;

    std::string status_code;
    response_stream >> status_code;
    response.status_code = status_code;

    std::string reason_phrase;
    std::getline(response_stream, reason_phrase);
    response.reason_phrase = reason_phrase;

    if (ec == boost::asio::error::eof) {
        lowest_layer_socket.close();
        return response;
    }
    // Get Response Headers
    boost::asio::read_until(ssl_socket, response_buffer, "\r\n\r\n", ec);
    std::string header;
    while (std::getline(response_stream, header) && header != "\r") {
        std::stringstream headers_stream(header);
        std::string key;
        headers_stream >> key;
        key.pop_back();
        std::string value;
        headers_stream >> value;
        response.headers.push_back(std::make_pair(key, value));
    }

    if (ec == boost::asio::error::eof) {
        lowest_layer_socket.close();
        return response;
    }

    // Get Message Body
    if (response_buffer.size() > 0) {
        std::stringstream ss;
        ss << &response_buffer;
        response.message_body.append(ss.str());
    }
    while (boost::asio::read(ssl_socket, response_buffer, ec)) {
        std::stringstream ss;
        ss << &response_stream;
        response.message_body.append(ss.str());
    }
    if (ec != boost::asio::error::eof) {
        // short read is closing of ssl socket notification from server.
        std::cout << ec.message() << std::endl;
    }

    lowest_layer_socket.close();
    return response;
}

void digest(const Response& response) {
    if (response.status_code != "200") {
        throw std::runtime_error("HTTP error. Reason: " +
                                 response.reason_phrase + ". Status Code: " +
                                 response.status_code);
    }
}

}  // namespace detail
}  // namespace tal
