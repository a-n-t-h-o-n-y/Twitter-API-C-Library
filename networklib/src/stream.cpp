#include <networklib/stream.hpp>

#include <functional>
#include <iostream>
#include <memory>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <networklib/detail/encode.hpp>
#include <networklib/detail/headers.hpp>
#include <networklib/detail/network.hpp>
#include <networklib/detail/parse.hpp>
#include <networklib/detail/socket.hpp>
#include <networklib/oauth/oauth.hpp>

namespace network {

Stream::Stream(const Request& request)
    : request_{request}, sock_stream_{std::make_unique<detail::Socket>()} {}

void Stream::register_function(Callback f1, Condition f2) {
    callbacks_mutex_.lock();
    callbacks_.push_back(std::make_pair(f1, f2));
    callbacks_mutex_.unlock();
}

// Builds the request and calls asio::write()
void Stream::open() {
    if (sock_stream_->socket_ptr != nullptr &&
        sock_stream_->socket_ptr->lowest_layer().is_open()) {
        return;
    }
    sock_stream_->socket_ptr = detail::make_connection(request_);
    auto buffer = boost::asio::buffer(std::string(request_));
    boost::asio::async_write(*sock_stream_->socket_ptr, buffer,
                             [this](const auto& ec, std::size_t bytes) {
                                 this->dispatch(ec, bytes);
                             });
}

// Disconnects from the streaming API.
void Stream::close() {
    if (sock_stream_->socket_ptr == nullptr) {
        return;
    }
    boost::system::error_code ec;
    sock_stream_->socket_ptr->lowest_layer().shutdown(
        boost::asio::ip::tcp::socket::shutdown_both, ec);
    // TODO: add error handling, check ec
    sock_stream_->socket_ptr->lowest_layer().close();
}

// Reads from the socket, creates Response objects and sends them to each
// callback. Checks for reconnect_ on beginning of every iteration.
void Stream::dispatch(const boost::system::error_code& ec,
                      std::size_t bytes_transfered) {
    reconnect_mtx_.lock();
    reconnect_ = false;
    reconnect_mtx_.unlock();
    boost::asio::streambuf buffer_read;
    detail::digest(detail::Status_line(*sock_stream_->socket_ptr, buffer_read));
    // Headers header(*sock_stream_);  // change to socket_ptr_ eventually
    // std::cout << header << std::endl;

    // if (header.get("transfer-encoding") != "chunked") {
    //     throw std::runtime_error("Stream transfer encoding is not chunked.");
    // }

    std::string message_str;
    while (!reconnect_) {  // how is reconnect_ set?
        // what about keep alive newlines?
        std::size_t pos{0};
        boost::asio::deadline_timer timer{
            sock_stream_->socket_ptr->get_io_service(),
            boost::posix_time::seconds(90)};
        while ((pos = message_str.find("\r\n")) == std::string::npos) {
            // timer_.expires_from_now(boost::posix_time::seconds(90));
            timer.async_wait(
                std::bind(&Stream::timer_expired, this, std::placeholders::_1));
            message_str.append(
                detail::read_chunk(*sock_stream_->socket_ptr, buffer_read));
            // timer_.expires_at(boost::posix_time::pos_infin);
            timer.cancel();
        }
        auto response = message_str.substr(0, pos);
        if (response.size() > 1) {
            this->send_response(Response{response});
            message_str.erase(0, pos + 2);
        } else {
            message_str.clear();
        }
    }
    // reconnect_ was set
    this->reconnect();
}

void Stream::reconnect() {
    this->close();
    this->open();
}

void Stream::timer_expired(const boost::system::error_code& ec) {
    // this->reconnect();
    this->close();
    std::cout << "Reconnecting..." << std::endl;
    this->open();
}

void Stream::send_response(const Response& response) {
    callbacks_mutex_.lock();
    for (auto& pair : callbacks_) {
        if (pair.second(response)) {
            pair.first(response);
        }
    }
    callbacks_mutex_.unlock();
}

}  // namespace network
