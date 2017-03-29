#include "stream.hpp"
#include "detail/oauth.hpp"
#include "detail/network.hpp"

#include <functional>
#include <sstream>

namespace tal {

Stream::Stream(App* app,
               std::string host,
               std::string uri,
               std::string method) {
    set_host(std::move(host));
    set_URI(std::move(uri));
    set_method(std::move(method));
}

void Stream::register_function(Callback f1, Condition f2) {
    callbacks_mutex_.lock();
    callbacks_.push_back(std::make_pair(f1, f2));
    callbacks_mutex_.unlock();
}

// Builds the complete request with endpoint and parameters.
Request Stream::build_request() {
    Request r;
    r.HTTP_method = get_method();
    r.host = get_host();
    r.URI = get_URI();
    r.content_type = "application/json";  // Might not need
    build_parameters(r);
}

// Only builds the shared parameters.
virtual void Stream::build_parameters(Request& r) {
    if (!parameters_.delimited.empty()) {
        r.add_query("delimited", parameters_.delimited)
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
    socket_ = detail::make_connection(r);
}

// Disconnects from the streaming API.
void Stream::end_connection() {
    socket_->lowest_layer().close();
}

// Reads from the socket, creates Response objects and sends them to each
// callback. Checks for reconnect_ on beginning of every iteration.
void Stream::dispatch(const boost::system::error_code ec& ec,
                      std::size_t bytes_transfered) {
    // In its own thread
    reconnect_mtx_.lock();
    reconnect_ = false;
    reconnect_mtx.unlock();
    while (!reconnect_) {
        Response r(socket_);
        callbacks_mutex_.lock();
        for (auto& pair : callbacks_) {
            if (pair.first(r)) {
                pair.second(r);
            }
        }
        callbacks_mutex_.unlock();
    }
    // If it makes it here, then reconnect_ was set true
    end_connection();
    run();
}

// builds the request and calls asio::write()
void Stream::run() {
    Request r = build_request();
    this->authorize(r);
    this->make_connection(r);
    boost::asio::async_write(
        *socket_, std::string(r),
        std::bind(Stream::dispatch, this, std::placeholders::_1,
                  std::placeholders::_2));
}

User_stream::User_stream(App* app)
    : Stream(app, "userstream.twitter.com", "/1.1/user.json", "GET") {}

void User_stream::authorize(Request& r) {
    detail::authorize(r, app_, app_->account());
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
    detail::authorize(r, app_);
}

}  // namespace tal
