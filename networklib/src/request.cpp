#include <networklib/request.hpp>

#include <sstream>
#include <string>

#include <networklib/detail/encode.hpp>

namespace network {

Request::operator std::string() const {
    // Encode message body
    std::string encoded_body{detail::key_value_encode(message_body)};

    std::stringstream request;
    // Request line
    request << HTTP_method << ' ' << URI;
    if (!queries.empty()) {
        request << '?';
        request << detail::key_value_encode(queries);
    }
    request << ' ' << HTTP_version << "\r\n";

    // Header
    request << "Accept: " << accept << "\r\n";
    // request << "Connection: " << connection << "\r\n";
    request << "User-Agent: " << user_agent << "\r\n";
    request << "Content-Type: " << content_type << "\r\n";
    if (!authorization.empty()) {
        request << "Authorization: " << authorization << "\r\n";
    }
    request << "Content-Length: " << encoded_body.length() << "\r\n";
    request << "Host: " << host << "\r\n";
    for (auto& key_value : extra_headers) {
        request << key_value.first << ": " << key_value.second << "\r\n";
    }
    request << "\r\n";

    // Message body
    request << encoded_body;

    return request.str();
}

void Request::add_query(const std::string& key, const std::string& value) {
    queries.push_back(std::make_pair(key, value));
}

void Request::add_message(const std::string& key, const std::string& value) {
    message_body.push_back(std::make_pair(key, value));
}

void Request::add_header(const std::string& key, const std::string& value) {
    extra_headers.push_back(std::make_pair(key, value));
}

}  // namespace network
