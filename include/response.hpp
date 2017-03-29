#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <vector>
#include <utility>
#include <ostream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tal {

class Response {
   public:
    Response() = default;
    explicit Response(
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& ssl_socket);

    /// Return response as string.
    explicit operator std::string() const;

    /// Finds value belonging to the given key from the header. Returns empty
    /// string if no header key found.
    std::string find_header(const std::string& key) const;

    // Status Line
    std::string HTTP_version;
    std::string status_code;
    std::string reason_phrase;

    // Header
    std::vector<std::pair<std::string, std::string>> headers;

    // Message Body
    std::string message_body;
};

inline std::ostream& operator<<(std::ostream& os, const Response& response) {
    return os << static_cast<std::string>(response);
}

}  // namespace tal

#endif  // RESPONSE_HPP
