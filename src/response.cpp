#include "response.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <iostream>
#include <sstream>
#include <string>

namespace tal {

Response::Response(
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& ssl_socket) {
    // Get Status Line Response
    boost::asio::streambuf response_buffer;
    boost::system::error_code ec;
    auto n = boost::asio::read_until(ssl_socket, response_buffer, "\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream status_stream(&response_buffer);
    status_stream >> this->HTTP_version;
    status_stream >> this->status_code;
    std::getline(status_stream, this->reason_phrase);
    
    // Get Response Headers
    n = boost::asio::read_until(ssl_socket, response_buffer, "\r\n\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::cout << n << std::endl;
    std::istream header_stream(&response_buffer);
    std::string header;
    while (std::getline(header_stream, header) ) { //&& header != "\r"
        std::istringstream iss{header};
        std::string key;
        iss >> key;
        key.pop_back(); // remove ':'
        std::ostringstream oss;
        oss << iss.rdbuf();
        std::string value{oss.str()};
        this->headers.push_back(std::make_pair(key, value));
    }

    // if (ec == boost::asio::error::eof) {
    //     return;
    // }

    // Get Message Body
    // if (response_buffer.size() > 0) {
    //     std::stringstream ss;
    //     ss << &response_buffer;
    //     this->message_body.append(ss.str());
    // }
    // while (boost::asio::read(ssl_socket, response_buffer, ec)) {
    //     std::stringstream ss;
    //     ss << &response_stream;
    //     this->message_body.append(ss.str());
    // }
    if (ec != boost::asio::error::eof) {
        // Short read is closing of ssl socket notification from server.
        // std::cout << ec.message() << std::endl;
    }
}

Response::operator std::string() const {
    std::stringstream response;
    // Status Line
    response << HTTP_version << ' ' << status_code << ' ' << reason_phrase
             << "\r\n";

    // Headers
    for (const auto& key_pair : headers) {
        response << key_pair.first << ": " << key_pair.second << "\r\n";
    }

    response << "\r\n";

    // Message Body
    response << message_body;
    return response.str();
}

std::string Response::find_header(const std::string& key) const {
    for (const auto& key_value : headers) {
        if (key_value.first == key) {
            return key_value.second;
        }
    }
    return "";
}

}  // namespace tal
