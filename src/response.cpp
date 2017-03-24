#include "response.hpp"

#include <sstream>
#include <string>

namespace tal {

Response::Response(const std::string& http_response) {
    
}

Response::operator std::string() const {
    std::stringstream response;
    // Status Line
    response << HTTP_version << ' ' << status_code << ' ' << reason_phrase
             << "\r\n";

    // Headers
    for (const auto& key_pair : headers) {
        response << key_pair.first << ": " << key_pair.second << "\r\n";
    }

    response << "\r\n";

    // Message Body
    response << message_body;
    return response.str();
}

std::string Response::find_header(const std::string& key) const {
    for (const auto& key_value : headers) {
        if (key_value.first == key) {
            return key_value.second;
        }
    }
    return "";
}

}  // namespace tal
