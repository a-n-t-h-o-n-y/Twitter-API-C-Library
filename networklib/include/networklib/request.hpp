#ifndef NETWORKLIB_REQUEST_HPP
#define NETWORKLIB_REQUEST_HPP
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace network {

/// Responsible for generating an HTTP Request string for a set of parameters.
class Request {
   public:
    /// Return as HTTP style Request string.
    explicit operator std::string() const;

    /// Add a query to the request.
    void add_query(const std::string& key, const std::string& value);

    /// Add a message to the request.
    void add_message(const std::string& key, const std::string& value);

    /// Add a header to the request.
    void add_header(const std::string& key, const std::string& value);

    // Request parameters
    std::string HTTP_method;
    std::string URI;
    std::vector<std::pair<std::string, std::string>> queries;
    std::string HTTP_version{"HTTP/1.1"};

    // Header parameters
    std::string accept{"*/*"};
    std::string connection{"close"};
    std::string user_agent{"Twitterbot/1.0"};
    std::string content_type{"application/x-www-form-urlencoded"};
    std::string HTTP_protocol{"https"};
    std::string authorization;
    std::string host{"api.twitter.com"};
    // other heading parameters, vector of pairs like others, put some of the
    // above into this as well
    std::vector<std::pair<std::string, std::string>> extra_headers;

    // Message body
    std::vector<std::pair<std::string, std::string>> message_body;
};

inline std::ostream& operator<<(std::ostream& os, const Request& request) {
    return os << static_cast<std::string>(request);
}

}  // namespace network
#endif  // NETWORKLIB_REQUEST_HPP
