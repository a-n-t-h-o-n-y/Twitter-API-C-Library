#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <string>
#include <vector>
#include <utility>
#include <ostream>
#include <boost/asio/streambuf.hpp>
#include "detail/types.hpp"

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

}  // namesapce tal
#endif  // HEADERS_HPP
