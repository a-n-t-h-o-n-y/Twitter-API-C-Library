#include <networklib/https_read.hpp>

#include <networklib/detail/gzip.hpp>
#include <networklib/detail/headers.hpp>
#include <networklib/detail/read_buffer.hpp>
#include <networklib/detail/read_socket.hpp>
#include <networklib/detail/status_line.hpp>
#include <networklib/response.hpp>
#include <networklib/socket.hpp>

namespace network {

auto https_read(Socket socket) -> Response
{
    auto buffer = boost::asio::streambuf{};

    // Read Response - Can Throw
    check_status(detail::parse_status_line(
        detail::read_status_line_bytes(socket, buffer)));

    auto const headers =
        detail::parse_headers(detail::read_header_field_bytes(socket, buffer));
    auto const content_length = get(headers, "content-length");
    auto response             = detail::flush_buffer(buffer);

    if (!content_length.empty()) {
        auto const length = std::stoi(content_length) - response.size();
        response.append(detail::read_length(socket, buffer, length));
    }
    else if (get(headers, "transfer-encoding") == "chunked") {
        auto chunk = std::string{};
        do {
            chunk = detail::read_chunk(socket, buffer);
            if (chunk != " ")
                response.append(std::move(chunk));
        } while (!chunk.empty());
    }

    socket.close();

    if (get(headers, "content-encoding") == "gzip")
        response = detail::decode_gzip(response);

    return Response{response};
}

}  // namespace network
