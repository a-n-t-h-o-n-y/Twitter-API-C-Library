#include <networklib/detail/headers.hpp>

#include <istream>
#include <sstream>
#include <string>
#include <utility>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <networklib/detail/socket_stream.hpp>

namespace network {
namespace detail {

Headers::Headers(Socket_stream& socket, Streambuf& buffer) {
    boost::system::error_code ec;
    boost::asio::read_until(socket, buffer, "\r\n\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::string line;
    std::string key;
    std::string value;
    std::istream header_stream(&buffer);
    while (std::getline(header_stream, line, '\n')) {
        if (line.size() > 2) {
            line.pop_back();
            auto pos = line.find(": ");
            key = std::string(std::begin(line), std::begin(line) + pos);
            value = std::string(std::begin(line) + pos + 2, std::end(line));
            this->headers_.push_back(std::make_pair(key, value));
        }
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

}  // namespace detail
}  // namespace network
