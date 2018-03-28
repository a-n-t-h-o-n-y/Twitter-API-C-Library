#include <networklib/detail/status_line.hpp>

#include <istream>
#include <sstream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <networklib/detail/socket_stream.hpp>

namespace network {
namespace detail {

Status_line::Status_line(Socket_stream& socket,
                         boost::asio::streambuf& buffer) {
    // boost::asio::streambuf buffer;
    boost::system::error_code ec;
    boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream status_stream(&buffer);
    status_stream >> this->HTTP_version;
    status_stream >> this->status_code;
    std::getline(status_stream, this->reason_phrase, '\r');
}

Status_line::operator std::string() const {
    std::stringstream status_stream;
    status_stream << HTTP_version << ' ' << status_code << ' ' << reason_phrase
                  << "\r\n";
    return status_stream.str();
}

}  // namespace detail
}  // namespace network
