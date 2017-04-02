#ifndef STREAM_HPP
#define STREAM_HPP

#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <cstddef>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "user.hpp"
#include "response.hpp"
#include "request.hpp"

namespace tal {
class App;

struct Stream_parameters {
    std::string delimited;
    bool stall_warnings;
    std::vector<std::string> track;
    std::pair<coordinates, coordinates> locations;
    bool use_locations_;

    std::string language;
    std::vector<twitter_id> follow;
    std::string filter_level;
    std::int16_t count;

    // User Stream Only
    std::string with;
    std::string replies;
    bool stringify_friend_ids;

    // Request Parameters
    std::string host;
    std::string URI;
    std::string method;
};

class Stream {
   public:
    using Callback = std::function<void(const Response&)>;
    using Condition = std::function<bool(const Response&)>;

    Stream(App* app, std::string host, std::string uri, std::string method);

    void register_function(Callback f1,
                           Condition f2 = [](const Response&) { return true; });

    // Parameters
    void set_delimited(std::string v) {
        parameters_.delimited = std::move(v);
        reconnect_ = true;
    }
    void set_stall_warnings(bool v) {
        parameters_.stall_warnings = v;
        reconnect_ = true;
    }
    void set_filter_level(std::string v) {
        parameters_.filter_level = std::move(v);
        reconnect_ = true;
    }
    void set_language(std::string v) {
        parameters_.language = std::move(v);
        reconnect_ = true;
    }
    void add_follow(twitter_id id) {
        parameters_.follow.push_back(id);
        reconnect_ = true;
    }
    bool remove_follow(twitter_id id) {
        auto pos = std::find(std::begin(parameters_.follow),
                             std::end(parameters_.follow), id);
        if (pos == std::end(parameters_.follow)) {
            return false;
        }
        parameters_.follow.erase(pos);
        reconnect_ = true;
        return true;
    }
    void add_track(std::string v) {
        parameters_.track.push_back(std::move(v));
        reconnect_ = true;
    }
    bool remove_track(const std::string& v) {
        auto pos = std::find(std::begin(parameters_.track),
                             std::end(parameters_.track), v);
        if (pos == std::end(parameters_.track)) {
            return false;
        }
        parameters_.track.erase(pos);
        reconnect_ = true;
        return true;
    }
    void set_locations(float lat_1, float lon_1, float lat_2, float lon_2) {
        parameters_.locations = std::make_pair(coordinates{lat_1, lon_1},
                                               coordinates{lat_2, lon_2});
        parameters_.use_locations_ = true;
        reconnect_ = true;
    }
    void set_locations(std::pair<coordinates, coordinates> v) {
        parameters_.locations = v;
        parameters_.use_locations_ = true;
        reconnect_ = true;
    }
    void unset_locations() {
        parameters_.use_locations_ = false;
        reconnect_ = true;
    }
    void set_count(std::int16_t v) {
        parameters_.count = v;
        reconnect_ = true;
    }
    void set_with(std::string v) {
        parameters_.with = std::move(v);
        reconnect_ = true;
    }
    void set_replies(std::string v) {
        parameters_.replies = std::move(v);
        reconnect_ = true;
    }
    void set_stringify_friend_ids(bool v) {
        parameters_.stringify_friend_ids = v;
        reconnect_ = true;
    }
    void set_host(std::string host) {
        parameters_.host = std::move(host);
        reconnect_ = true;
    }
    void set_URI(std::string uri) {
        parameters_.URI = std::move(uri);
        reconnect_ = true;
    }
    void set_method(std::string method) {
        parameters_.method = std::move(method);
        reconnect_ = true;
    }

    // Get
    std::string get_delimited() const { return parameters_.delimited; }
    bool get_stall_warnings() const { return parameters_.stall_warnings; }
    std::string get_filter_level() const { return parameters_.filter_level; }
    std::string get_language() const { return parameters_.language; }
    std::vector<twitter_id> get_follow() const { return parameters_.follow; }
    std::vector<std::string> get_track() const { return parameters_.track; }
    std::pair<coordinates, coordinates> get_locations() const {
        return parameters_.locations;
    }
    std::int16_t get_count() const { return parameters_.count; }
    std::string get_with() const { return parameters_.with; }
    std::string get_replies() const { return parameters_.replies; }
    bool get_stringify_friend_ids() const {
        return parameters_.stringify_friend_ids;
    }
    std::string get_host() const { return parameters_.host; }
    std::string get_URI() const { return parameters_.URI; }
    std::string get_method() const { return parameters_.method; }

   protected:
    using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

    std::unique_ptr<ssl_socket> socket_;
    std::vector<std::pair<Callback, Condition>> callbacks_;
    std::mutex callbacks_mutex_;
    Stream_parameters parameters_;
    bool reconnect_{false};
    std::mutex reconnect_mtx_;
    std::string endpoint_;
    App* app_;

    // Builds the complete request with endpoint and parameters.
    Request build_request();

    // Only builds the shared parameters.
    virtual void build_parameters(Request& r);

    virtual void authorize(Request& r) = 0;

    // Makes and stores the connection. Called by run().
    void make_connection(const Request& r);

    // Disconnects from the streaming API.
    void end_connection();

    // Reads from the socket, creates Response objects and sends them to each
    // callback. Checks for reconnect_ on beginning of every iteration.
    void dispatch(const boost::system::error_code& ec,
                  std::size_t bytes_transfered);

    // Starts the async pulling of objects off the Stream.
    // calls asio::write(socket_, bind(dispatch(this)));
    void run();  // reconnect_ = false; in-case it has been set before start
};

class User_stream : public Stream {
   public:
    User_stream(App* app);

   private:
    // Calls down to the base implementation and adds on extra user params.
    virtual void build_parameters(Request& r) override;
    virtual void authorize(Request& r) override;
};

class Public_stream : public Stream {
   public:
Public_stream(App* app, std::string uri, std::string method);

   private:
    virtual void authorize(Request& r) override;
};

}  // namespace tal
#endif  // STREAM_HPP
