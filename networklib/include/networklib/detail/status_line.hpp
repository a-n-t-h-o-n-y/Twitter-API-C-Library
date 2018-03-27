#ifndef STATUS_LINE_HPP
#define STATUS_LINE_HPP
#include <ostream>
#include <string>

#include <boost/asio/streambuf.hpp>

#include <networklib/detail/types.hpp>

namespace tal {

struct Status_line {
    Status_line(ssl_socket& socket, boost::asio::streambuf& buffer);
    explicit operator std::string() const;

    std::string HTTP_version;
    std::string status_code;
    std::string reason_phrase;
};

inline std::ostream& operator<<(std::ostream& os, const Status_line& status) {
    return os << static_cast<std::string>(status);
}

}  // namespace tal
#endif  // STATUS_LINE_HPP
