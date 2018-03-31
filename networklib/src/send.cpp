#include <networklib/send.hpp>

#include <ostream>
#include <string>

#include <networklib/detail/encode.hpp>
#include <networklib/detail/gzip.hpp>
#include <networklib/detail/headers.hpp>
#include <networklib/detail/make_connection.hpp>
#include <networklib/detail/read_socket.hpp>
#include <networklib/detail/status_line.hpp>
#include <networklib/request.hpp>

namespace network {

Response send(const Request& request) {
    auto socket_ptr = detail::make_connection(request);
    // Send request
    std::string r_str{request};
    boost::asio::write(*socket_ptr, boost::asio::buffer(r_str));

    // Read Response - can throw
    boost::asio::streambuf buffer_read;
    detail::digest(detail::Status_line(*socket_ptr, buffer_read));

    auto header = detail::Headers(*socket_ptr, buffer_read);
    std::string content_length = header.get("content-length");
    std::string response;
    if (!content_length.empty()) {
        auto length = std::stoi(content_length);
        response = detail::read_length(*socket_ptr, length, buffer_read);
    } else if (header.get("transfer-encoding") == "chunked") {
        while (true) {
            std::string chunk{detail::read_chunk(*socket_ptr, buffer_read)};
            if (chunk.empty()) {
                break;
            }
            if (chunk != " ") {
                response.append(chunk);
            }
        }
    }
    if (header.get("content-encoding") == "gzip") {
        detail::decode_gzip(response);
    }

    socket_ptr->lowest_layer().close();
    return Response(response);
}

}  // namespace network
