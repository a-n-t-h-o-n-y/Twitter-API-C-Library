#ifndef NETWORKLIB_STREAM_HPP
#define NETWORKLIB_STREAM_HPP
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include <networklib/request.hpp>

namespace boost {
namespace system {
class error_code;
}  // namespace system
}  // namespace boost

namespace network {
class Response;

namespace detail {
struct Socket;
}  // namespace detail

class Stream {
   public:
    using Callback = std::function<void(const Response&)>;
    using Condition = std::function<bool(const Response&)>;

    /// Create an asynchronous Stream object with an authorized Request. Does
    /// not open the stream.
    Stream(const Request& request = Request());
    ~Stream();

    /// Register a callback function to the stream which will be called when the
    /// Stream is open and a Response had been received.
    void register_function(Callback f1,
                           Condition f2 = [](const Response&) { return true; });

    /// Connects to the Stream endpoing and begins processing Responses.
    void open();

    /// Shuts down the stream, stopping processing.
    void close();

    /// Close and then reopen the stream.
    void reconnect();

    void set_request(const Request& r);

   private:
    Request request_;

    std::unique_ptr<detail::Socket> sock_stream_;

    std::vector<std::pair<Callback, Condition>> callbacks_;
    std::mutex callbacks_mutex_;

    bool reconnect_{false};
    std::mutex reconnect_mtx_;

    // Sends to all functions registered to this Stream.
    void send_response(const Response& response);

    void timer_expired(const boost::system::error_code& ec);

    // Reads from the socket, creates Response objects and sends them to
    // each callback. Checks for reconnect_ on beginning of every iteration.
    void dispatch(const boost::system::error_code& ec,
                  std::size_t bytes_transferred);
};

}  // namespace network
#endif  // NETWORKLIB_STREAM_HPP
