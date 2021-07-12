#ifndef NETWORKLIB_DETAIL_HEADERS_HPP
#define NETWORKLIB_DETAIL_HEADERS_HPP
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include <networklib/detail/socket_stream.hpp>

namespace network {
namespace detail {

class Headers {
   public:
    Headers(Socket_stream& socket, Streambuf& buffer);
    explicit operator std::string() const;
    auto get(const std::string& key) const -> std::string;

   private:
    std::vector<std::pair<std::string, std::string>> headers_;
};

inline auto operator<<(std::ostream& os, const Headers& h) -> std::ostream&
{
    return os << static_cast<std::string>(h);
}

}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_HEADERS_HPP
