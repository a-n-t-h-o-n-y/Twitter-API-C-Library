#include "stream.hpp"

#include <functional>
#include <sstream>
#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "app.hpp"
#include "detail/oauth.hpp"
#include "detail/network.hpp"
#include "detail/parse.hpp"
#include "detail/encode.hpp"
#include "headers.hpp"

namespace tal {

Stream::Stream(App* app, std::string host, std::string uri, std::string method)
    : app_{app} {
    timer_ptr_ =
        std::make_unique<boost::asio::deadline_timer>(app->io_service());
    set_host(std::move(host));  // why are these down here and not intitialized?
    set_URI(std::move(uri));
    set_method(std::move(method));
}

void Stream::register_function(Callback f1, Condition f2) {
    callbacks_mutex_.lock();
    callbacks_.push_back(std::make_pair(f1, f2));
    callbacks_mutex_.unlock();
    if (socket_ == nullptr) {
        this->run();
    }
}

// Builds the complete request with endpoint and parameters.
Request Stream::build_request() {
    Request r;
    r.HTTP_method = get_method();
    r.host = get_host();
    r.URI = get_URI();
    r.content_type = "application/json";  // Might not need
    build_parameters(r);
    return r;
}

// Only builds the shared parameters.
void Stream::build_parameters(Request& r) {
    if (!parameters_.delimited.empty()) {
        r.add_query("delimited", parameters_.delimited);
    }
    r.add_query("stall_warnings",
                parameters_.stall_warnings ? "true" : "false");
    if (!parameters_.track.empty()) {
        std::stringstream ss;
        std::string comma;
        for (auto& str : parameters_.track) {
            ss << comma << str;
            comma = ",";
        }
        r.add_query("track", ss.str());
    }
    if (parameters_.use_locations_) {
        std::stringstream ss;
        ss << parameters_.locations.first.longitude << ',';
        ss << parameters_.locations.first.lattitude << ',';
        ss << parameters_.locations.second.longitude << ',';
        ss << parameters_.locations.second.lattitude;
        r.add_query("locations", ss.str());
    }
    if (!parameters_.follow.empty()) {
        std::stringstream ss;
        std::string comma;
        for (auto& id : parameters_.follow) {
            ss << comma << id;
            comma = ",";
        }
        r.add_query("follow", ss.str());
    }
}

// Makes and stores the connection. Called by run().
void Stream::make_connection(const Request& r) {
    socket_ = detail::make_connection(r, app_->io_service());
}

// Disconnects from the streaming API.
void Stream::end_connection() {
    socket_->lowest_layer().close();
}

// Reads from the socket, creates Response objects and sends them to each
// callback. Checks for reconnect_ on beginning of every iteration.
void Stream::dispatch(const boost::system::error_code& ec,
                      std::size_t bytes_transfered) {
    reconnect_mtx_.lock();
    reconnect_ = false;
    reconnect_mtx_.unlock();
    boost::asio::streambuf buffer_read;
    detail::digest(Status_line(*socket_, buffer_read));
    // Headers header(*socket_);  // change to socket_ptr_ eventually
    // std::cout << header << std::endl;

    // if (header.get("transfer-encoding") != "chunked") {
    //     throw std::runtime_error("Stream transfer encoding is not chunked.");
    // }

    std::string message_str;
    while (!reconnect_) {
        // what about keep alive newlines?
        std::size_t pos{0};
        while ((pos = message_str.find("\r\n")) == std::string::npos) {
            timer_ptr_->expires_from_now(boost::posix_time::seconds(90));
            timer_ptr_->async_wait(
                std::bind(&Stream::timer_expired, this, std::placeholders::_1));
            message_str.append(detail::read_chunk(*socket_, buffer_read));
            timer_ptr_->expires_at(boost::posix_time::pos_infin);
        }
        auto message = message_str.substr(0, pos);
        // if (header.get("content-encoding") == "gzip") {
        //     detail::decode_gzip(message);
        // }
        if (message.size() > 1) {
            this->send_message(Message{message});
            message_str.erase(0, pos + 2);
        } else {
            message_str.clear();
        }
    }
    // If it makes it here, then reconnect_ was set true
    end_connection();
    run();
}

void Stream::timer_expired(boost::system::error_code ec) {
    end_connection();
    std::cout << "Reconnecting..." << std::endl;
    run();
}

void Stream::send_message(const Message& message) {
    callbacks_mutex_.lock();
    for (auto& pair : callbacks_) {
        if (pair.second(message)) {
            pair.first(message);
        }
    }
    callbacks_mutex_.unlock();
}

// builds the request and calls asio::write()
void Stream::run() {
    Request r = build_request();
    this->authorize(r);
    this->make_connection(r);
    boost::asio::async_write(
        *socket_, boost::asio::buffer(std::string(r)),
        std::bind(&Stream::dispatch, this, std::placeholders::_1,
                  std::placeholders::_2)); // use lambda
}

User_stream::User_stream(App* app)
    : Stream(app, "userstream.twitter.com", "/1.1/user.json", "GET") {}

void User_stream::authorize(Request& r) {
    detail::authorize(r, *app_, app_->account());
}

void User_stream::build_parameters(Request& r) {
    Stream::build_parameters(r);
    if (!parameters_.with.empty()) {
        r.add_query("with", parameters_.with);
    }
    if (!parameters_.replies.empty()) {
        r.add_query("replies", parameters_.replies);
    }
    r.add_query("stringify_friend_ids",
                parameters_.stringify_friend_ids ? "true" : "false");
}

Public_stream::Public_stream(App* app, std::string uri, std::string method)
    : Stream(app, "stream.twitter.com", uri, method) {}

void Public_stream::authorize(Request& r) {
    // detail::authorize(r, *app_);
    detail::authorize(r, *app_, app_->account());
}

}  // namespace tal
