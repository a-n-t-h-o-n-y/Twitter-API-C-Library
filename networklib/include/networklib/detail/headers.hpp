#ifndef NETWORKLIB_DETAIL_HEADERS_HPP
#define NETWORKLIB_DETAIL_HEADERS_HPP
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/asio/streambuf.hpp>

#include <networklib/detail/types.hpp>

namespace tal {

class Headers {
   public:
    Headers(ssl_socket& socket, boost::asio::streambuf& buffer);
    explicit operator std::string() const;
    std::string get(const std::string& key) const;

   private:
    std::vector<std::pair<std::string, std::string>> headers_;
};

inline std::ostream& operator<<(std::ostream& os, const Headers& h) {
    return os << static_cast<std::string>(h);
}

}  // namespace tal
#endif  // NETWORKLIB_DETAIL_HEADERS_HPP
