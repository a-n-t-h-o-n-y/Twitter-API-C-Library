#include <networklib/detail/status_line.hpp>

#include <istream>
#include <iterator>
#include <sstream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/system/error_code.hpp>

#include <networklib/detail/socket_stream.hpp>

namespace network::detail {

void check_status(Status_line const& status)
{
    if (status.status_code != "200") {
        auto ss = std::ostringstream{};
        ss << "HTTP error. Reason: ";
        ss << status.reason_phrase;
        ss << ". Status Code: ";
        ss << status.status_code;
        throw std::runtime_error(ss.str());
    }
}

auto read_status_line_bytes(Socket& socket, Streambuf& buffer) -> std::string
{
    auto const n = boost::asio::read_until(socket.get(), buffer, "\r\n");
    auto result  = std::string(n, '\n');
    {
        auto is = std::istream{&buffer};
        is.read(result.data(), n);
    }
    result.pop_back();  // '\n'
    result.pop_back();  // '\r'
    return result;
}

auto parse_status_line(std::string_view bytes) -> Status_line
{
    auto result = Status_line{};
    auto iss    = std::istringstream{std::string{bytes}};
    iss >> result.HTTP_version;
    iss >> result.status_code;
    std::getline(iss >> std::ws, result.reason_phrase);
    return result;
}

auto to_string(Status_line const& x) -> std::string
{
    auto result = std::string{};
    return result.append(x.HTTP_version)
        .append(1, ' ')
        .append(x.status_code)
        .append(1, ' ')
        .append(x.reason_phrase)
        .append("\r\n");
}

auto operator<<(std::ostream& os, Status_line const& x) -> std::ostream&
{
    os << to_string(x);
    return os;
}

}  // namespace network::detail
