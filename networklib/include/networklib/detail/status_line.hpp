#ifndef NETWORKLIB_DETAIL_STATUS_LINE_HPP
#define NETWORKLIB_DETAIL_STATUS_LINE_HPP
#include <ostream>
#include <string>

#include <boost/asio/streambuf.hpp>

#include <networklib/detail/types.hpp>

namespace network {
namespace detail {

struct Status_line {
    Status_line(detail::ssl_socket& socket, boost::asio::streambuf& buffer);
    explicit operator std::string() const;

    std::string HTTP_version;
    std::string status_code;
    std::string reason_phrase;
};

inline std::ostream& operator<<(std::ostream& os, const Status_line& status) {
    return os << static_cast<std::string>(status);
}

}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_STATUS_LINE_HPP
