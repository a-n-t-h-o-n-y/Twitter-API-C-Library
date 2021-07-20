#include <networklib/request.hpp>

#include <ostream>
#include <sstream>
#include <string>

#include <networklib/detail/encode.hpp>

namespace network {

auto to_string(Request const& x) -> std::string
{
    constexpr char const* CR = "\r\n";

    auto encoded_body = detail::key_value_encode(x.messages);
    auto result       = std::string{};

    // Request Line
    result.append(x.HTTP_method).append(1, ' ').append(x.URI);
    if (!x.queries.empty())
        result.append(1, '?').append(detail::key_value_encode(x.queries));

    result.append(1, ' ').append(x.HTTP_version).append(CR);

    // Header
    result.append("Accept: ").append(x.accept).append(CR);
    result.append("User-Agent: ").append(x.user_agent).append(CR);
    result.append("Content-Type: ").append(x.content_type).append(CR);

    if (!x.authorization.empty())
        result.append("Authorization: ").append(x.authorization).append(CR);

    result.append("Content-Length: ")
        .append(std::to_string(encoded_body.length()))
        .append(CR);

    result.append("Host: ").append(x.host).append(CR);
    for (auto const& [key, value] : x.headers)
        result.append(key).append(": ").append(value).append(CR);

    // Message Body
    result.append(CR).append(std::move(encoded_body));
    return result;
}

auto operator<<(std::ostream& os, Request const& request) -> std::ostream&
{
    return os << to_string(request);
}

}  // namespace network
