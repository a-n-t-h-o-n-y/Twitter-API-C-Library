#ifndef NETWORKLIB_REQUEST_HPP
#define NETWORKLIB_REQUEST_HPP
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace network {

/// HTTP Request Parameters
struct Request {
    // Request Parameters
    std::string HTTP_method;
    std::string URI;
    std::vector<std::pair<std::string, std::string>> queries;
    std::string HTTP_version{"HTTP/1.1"};

    // Header Parameters
    std::string accept{"*/*"};
    std::string connection{"close"};
    std::string user_agent{"Twitterbot/1.0"};
    std::string content_type{"application/x-www-form-urlencoded"};
    std::string HTTP_protocol{"https"};
    std::string authorization;
    std::string host{"api.twitter.com"};
    std::vector<std::pair<std::string, std::string>> headers;

    // Message Body
    std::vector<std::pair<std::string, std::string>> messages;
};

/// Return the HTTP request string for \p x.
[[nodiscard]] auto to_string(Request const& x) -> std::string;

auto operator<<(std::ostream& os, Request const& request) -> std::ostream&;

}  // namespace network
#endif  // NETWORKLIB_REQUEST_HPP
