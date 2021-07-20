#include <networklib/detail/headers.hpp>

#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <networklib/detail/socket_stream.hpp>

namespace network::detail {

auto get(Headers const& headers, std::string const& key) -> std::string
{
    for (auto const& [k, v] : headers) {
        if (k == key)
            return v;
    }
    return "";
}

auto read_header_field_bytes(Socket& socket, Streambuf& buffer) -> std::string
{
    auto const n = boost::asio::read_until(socket.get(), buffer, "\r\n\r\n");
    auto result  = std::string(n, '\n');
    {
        auto is = std::istream{&buffer};
        is.read(result.data(), n);
    }
    result.pop_back();  // '\n'
    result.pop_back();  // '\r'
    result.pop_back();  // '\n'
    result.pop_back();  // '\r'
    return result;
}

auto parse_headers(std::string_view bytes) -> Headers
{
    auto result = Headers{};
    auto iss    = std::istringstream{std::string{bytes}};
    auto line   = std::string{};
    while (std::getline(iss >> std::ws, line, '\n')) {
        auto const pos = line.find(":");
        if (pos == std::string::npos)
            throw std::runtime_error{"parse_headers: Invalid; can't find ':'."};
        auto key   = std::string(std::cbegin(line), std::cbegin(line) + pos);
        auto value = std::string(std::cbegin(line) + pos + 2, std::cend(line));
        result.push_back({std::move(key), std::move(value)});
    }
    return result;
}

auto to_string(Headers const& x) -> std::string
{
    auto oss = std::ostringstream{};
    for (auto const& [key, value] : x)
        oss << key << ": " << value << "\r\n";
    oss << "\r\n";
    return oss.str();
}

auto operator<<(std::ostream& os, Headers const& x) -> std::ostream&
{
    os << to_string(x);
    return os;
}

}  // namespace network::detail
