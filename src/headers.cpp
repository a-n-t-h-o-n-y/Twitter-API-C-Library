#include "headers.hpp"

#include <string>
#include <istream>
#include <utility>
#include <sstream>
#include <iostream> // temp

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "detail/types.hpp"

namespace tal {

Headers::Headers(ssl_socket& socket) {
    boost::asio::streambuf buffer;
    boost::system::error_code ec;
    auto n = boost::asio::read_until(socket, buffer, "\r\n\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream header_stream(&buffer);
    //
    std::string out(n, ' ');
    header_stream.read(&out[0], n);
    std::cout << out << std::endl;
    //
    std::string key;
    std::string value;
    // value needs to be a getline, it can have spaces
    while(header_stream >> key >> value) {
        key.pop_back(); // Remove :
        this->headers_.push_back(std::make_pair(key, value));
    }
}

Headers::operator std::string() const {
    std::stringstream header_stream;
    for (const auto& key_pair : headers_) {
        header_stream << key_pair.first << ": " << key_pair.second << "\r\n";
    }
    header_stream << "\r\n";
    return header_stream.str();
}

std::string Headers::get(const std::string& key) const {
    for (const auto& key_value : headers_) {
        if (key_value.first == key) {
            return key_value.second;
        }
    }
    return "";
}

}  // namespace tal
