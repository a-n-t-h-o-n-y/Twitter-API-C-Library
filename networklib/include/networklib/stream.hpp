#ifndef STREAM_HPP
#define STREAM_HPP
#include <cstddef>
#include <functional>
#include <mutex>
#include <utility>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <networklib/detail/network.hpp>
#include <networklib/detail/types.hpp>
#include <networklib/message.hpp>
#include <networklib/request.hpp>

namespace tal {

class Stream {
   public:
    using Callback = std::function<void(const Message&)>;
    using Condition = std::function<bool(const Message&)>;

    /// Create an asynchronous Stream object with an authorized Request. Does
    /// not open the stream.
    Stream(const Request& request);

    /// Register a callback function to the stream which will be called when the
    /// Stream is open and a Response had been recieved.
    void register_function(Callback f1,
                           Condition f2 = [](const Message&) { return true; });

    /// Connects to the Stream endpoing and begins processing Responses.
    void open();

    /// Shuts down the stream, stopping processing.
    void close();

   private:
    boost::asio::deadline_timer timer_{detail::io_service(),
                                       boost::posix_time::seconds(90)};
    Request request_;

    using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;
    std::unique_ptr<ssl_socket> sock_stream_{nullptr};

    std::vector<std::pair<Callback, Condition>> callbacks_;
    std::mutex callbacks_mutex_;

    bool reconnect_{false};
    std::mutex reconnect_mtx_;

    // Sends to all functions registered to this Stream.
    void send_message(const Message& message);

    // Makes and stores the connection. Called by run().
    void make_connection(const Request& r);

    void timer_expired(boost::system::error_code ec);

    // Reads from the socket, creates Response objects and sends them to
    // each callback. Checks for reconnect_ on beginning of every iteration.
    void dispatch(const boost::system::error_code& ec,
                  std::size_t bytes_transfered);
};

}  // namespace tal
#endif  // STREAM_HPP
