#include <networklib/stream.hpp>

#include <memory>
#include <string>
#include <utility>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/system/error_code.hpp>

#include <networklib/detail/encode.hpp>
#include <networklib/detail/headers.hpp>
#include <networklib/detail/read_socket.hpp>
#include <networklib/detail/status_line.hpp>
#include <networklib/response.hpp>
#include <networklib/socket.hpp>

namespace network {

auto Stream::Stream_impl::launch(Request const& request, Callback callback)
    -> std::shared_ptr<Stream_impl>
{
    auto stream_ptr = std::make_shared<Stream_impl>(
        request.host, request.HTTP_protocol, std::move(callback));

    // Storing a shared_ptr to the stream so actions_ and socket_ are not
    // destroyed before this handler is.
    boost::asio::async_write(
        stream_ptr->socket_.get(), boost::asio::buffer(to_string(request)),
        [stream_ptr](auto ec, auto) { stream_ptr->process_chunks(ec); });

    return stream_ptr;
}

void Stream::Stream_impl::kill() { alive_ = false; }

Stream::Stream_impl::Stream_impl(std::string const& host,
                                 std::string const& service,
                                 Callback callback)
    : socket_{Socket::make_connection(host, service)},
      callback_{std::move(callback)}
{}

void Stream::Stream_impl::process_chunks(boost::system::error_code ec)
{
    if (ec != boost::system::errc::success)
        throw boost::system::system_error{ec};

    auto read_buffer = boost::asio::streambuf{};

    check_status(detail::parse_status_line(
        detail::read_status_line_bytes(socket_, read_buffer)));

    {  // Read headers and verify tranfer-encoding is chunked.
        auto const headers = detail::parse_headers(
            detail::read_header_field_bytes(socket_, read_buffer));
        if (get(headers, "transfer-encoding") != "chunked")
            throw std::runtime_error{"Stream: transfer-encoding not chunked."};
    }

    auto message_str = std::string{};
    while (alive_) {
        auto pos = std::string::npos;
        while (pos == std::string::npos) {
            message_str.append(detail::read_chunk(socket_, read_buffer));
            pos = message_str.find("\r\n");
        }

        if (pos > 1)
            callback_(Response{message_str.substr(0, pos)});

        message_str.erase(0, pos + 2);
    }
}

auto Stream::launch(Request const& request, Callback callback) -> Stream
{
    return Stream{Stream_impl::launch(request, std::move(callback))};
}

Stream::Stream(std::shared_ptr<Stream_impl> ptr) : ptr_{std::move(ptr)} {}

Stream::~Stream() { ptr_->kill(); }

}  // namespace network
