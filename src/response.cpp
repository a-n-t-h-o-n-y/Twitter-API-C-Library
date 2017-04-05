#include "response.hpp"
#include "detail/encode.hpp"
#include "detail/network.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

#include <iostream>
#include <sstream>
#include <string>

namespace tal {

// Response::Response(ssl_socket& socket, bool b) {
//     // most likely chunked and possibly gzipped if option set.
//     // pull out those pieces from the other Response constructor

//     // boost::asio::streambuf response_buffer;
//     // boost::system::error_code ec;
//     // auto n = boost::asio::read_until(socket, response_buffer, "\r\n", ec);
//     // if (ec && ec != boost::asio::error::eof) {
//     //     throw boost::system::system_error(ec);
//     // }
//     // std::istream response_stream(&response_buffer);
//     // std::string rs(n, ' ');
//     // response_stream.read(&rs[0], n);
//     // std::cout << rs;
//     boost::asio::streambuf response_buffer;
//     boost::system::error_code ec;
//     auto n = boost::asio::read_until(socket, response_buffer, "\r\n", ec);
//     if (ec && ec != boost::asio::error::eof) {
//         throw boost::system::system_error(ec);
//     }
//     std::istream response_stream(&response_buffer);
//     response_stream >> this->HTTP_version;
//     response_stream >> this->status_code;
//     std::getline(response_stream, this->reason_phrase);

//     // Get Response Headers
//     n = boost::asio::read_until(socket, response_buffer, "\r\n\r\n", ec);
//     if (ec && ec != boost::asio::error::eof) {
//         throw boost::system::system_error(ec);
//     }
//     std::string headers_s(n, ' ');
//     response_stream.read(&headers_s[0], n);
//     std::stringstream headers_ss{headers_s};
//     std::string header;
//     while (std::getline(headers_ss, header) && header != "\r") {
//         std::istringstream iss{header};
//         std::string key;
//         iss >> key;
//         if (!key.empty()) {
//             key.pop_back();  // remove ':'
//         }
//         std::string value(++std::istreambuf_iterator<char>(iss), {});
//         // Remove trailing whitespace
//         auto pos = value.find_last_not_of(" \r\n");
//         if (pos != std::string::npos) {
//             value.erase(pos + 1);
//         }
//         this->headers.push_back(std::make_pair(key, value));
//     }
// }

// Response::Response(ssl_socket& socket) {
//     // Get Status Line Response
//     // boost::asio::streambuf response_buffer;
//     // boost::system::error_code ec;
//     // auto n = boost::asio::read_until(socket, response_buffer, "\r\n", ec);
//     // if (ec && ec != boost::asio::error::eof) {
//     //     throw boost::system::system_error(ec);
//     // }
//     // std::istream response_stream(&response_buffer);
//     // response_stream >> this->HTTP_version;
//     // response_stream >> this->status_code;
//     // std::getline(response_stream, this->reason_phrase);

//     // Get Response Headers
//     // n = boost::asio::read_until(socket, response_buffer, "\r\n\r\n", ec);
//     // if (ec && ec != boost::asio::error::eof) {
//     //     throw boost::system::system_error(ec);
//     // }
//     // std::string headers_s(n, ' ');
//     // response_stream.read(&headers_s[0], n);
//     // std::stringstream headers_ss{headers_s};
//     // std::string header;
//     // while (std::getline(headers_ss, header) && header != "\r") {
//     //     std::istringstream iss{header};
//     //     std::string key;
//     //     iss >> key;
//     //     if (!key.empty()) {
//     //         key.pop_back();  // remove ':'
//     //     }
//     //     std::string value(++std::istreambuf_iterator<char>(iss), {});
//     //     // Remove trailing whitespace
//     //     auto pos = value.find_last_not_of(" \r\n");
//     //     if (pos != std::string::npos) {
//     //         value.erase(pos + 1);
//     //     }
//     //     this->headers.push_back(std::make_pair(key, value));
//     // }

//     // if (ec == boost::asio::error::eof) {
//     //     return;
//     // }

//     // Get Message Body
//     // Search for content-length in *this
//     std::string cl_value = this->find_header("content-length");
//     std::size_t message_length{0};
//     if (!cl_value.empty()) {
//         message_length = std::stoi(cl_value);
//         // n = boost::asio::read(socket, response_buffer,
//         //                       boost::asio::transfer_exactly(message_length),
//         //                       ec);
//         // // read n bytes out of response_buffer and into string
//         // this->message_body = std::string(n, ' ');
//         // response_stream.read(&this->message_body[0], n);
//     } else if (find_header("transfer-encoding") == "chunked") {
//         // Read chunked message body
//         // this->message_body = detail::read_chunked_body(socket);
//         // n = boost::asio::read(socket, response_buffer, ec);
//     }
//     // if (ec && ec != boost::asio::error::eof) {
//     //     throw boost::system::system_error(ec);
//     // }

//     std::string encoding = this->find_header("content-encoding");
//     if (encoding == "gzip" || encoding == "x-gzip") {
//         detail::decode_gzip(this->message_body);
//     }

//     // if (ec && ec != boost::asio::error::eof) {
//     //     throw boost::system::system_error(ec);
//     // }
// }

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

}  // namespace tal
