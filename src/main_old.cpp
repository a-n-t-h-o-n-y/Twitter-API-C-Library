#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <string>

#include "detail/oauth.hpp"

using namespace boost::asio;

int main() {
    ssl::context ctx(ssl::context::sslv23);
    ctx.set_verify_mode(ssl::verify_peer);
    ctx.set_default_verify_paths();

    io_service io_s;

    ssl::stream<ip::tcp::socket> ssl_socket(io_s, ctx);
    auto& lowest_layer_socket = ssl_socket.lowest_layer();

    ip::tcp::resolver resolver(io_s);
    ip::tcp::resolver::query query("api.twitter.com", "https");
    ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    connect(lowest_layer_socket, endpoint_iterator);
    ssl_socket.handshake(ssl::stream<ip::tcp::socket>::client);

    // send request
    streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET "
                   << "1.1/search/tweets.json"
                   << " HTTP/1.0\r\n";
    request_stream << "Host: "
                   << "api.twitter.com"
                   << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";

    write(ssl_socket, request);

    streambuf response;
    read_until(ssl_socket, response, "\r\n");

    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
        std::cout << "Invalid response\n";
        return 1;
    }
    if (status_code != 200) {
        std::cout << "Response returned with status code " << status_code
                  << "\n";
        return 1;
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(ssl_socket, response, "\r\n\r\n");

    // Process the response headers.
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
        std::cout << header << "\n";
    std::cout << "\n";

    // Write whatever content we already have to output.
    if (response.size() > 0)
        std::cout << &response;

    // Read until EOF, writing data to output as we go.
    boost::system::error_code error;
    while (boost::asio::read(ssl_socket, response,
                             boost::asio::transfer_at_least(1), error))
        std::cout << &response;
    if (error != boost::asio::error::eof)
        throw boost::system::system_error(error);

    // ssl_socket.shutdown();
    lowest_layer_socket.close();

    return 0;
}
