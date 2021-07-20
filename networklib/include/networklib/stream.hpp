#ifndef NETWORKLIB_STREAM_HPP
#define NETWORKLIB_STREAM_HPP
#include <atomic>
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/socket.hpp>

namespace boost::system {
class error_code;
}  // namespace boost::system

namespace network {

/// A long running connection with a single Request and multiple reads.
/** Each read result is given to a predicate and then potentially a callback to
 *  handle the new data. Objects of this type represent active streams, they can
 *  only be created with the static `launch` method, the destructor will
 *  shutdown the Stream. Recommended to hold in a std::optional if reconnecting
 *  or delayed start is required. */
class Stream {
   public:
    using Callback = std::function<void(Response const&)>;

   private:
    // Needed so shared_ptr can be stored and handler can determine when to
    // destroy the object.
    class Stream_impl {
       public:
        /// Uses \p request to create a streaming https connection.
        /** \p callback is invoked with each chunk of received data. */
        [[nodiscard]] static auto launch(Request const& request,
                                         Callback callback)
            -> std::shared_ptr<Stream_impl>;

       public:
        /// Tell the handler to shutdown.
        /** Will not work if read_chunk never returns with valid output. */
        void kill();

       public:  // public for make_shared
        Stream_impl(std::string const& host,
                    std::string const& service,
                    Callback callback);

       private:
        Socket socket_;
        Callback callback_;
        std::atomic<bool> alive_ = true;

       private:
        /// Endlessly read each chunk from the Socket; invoke callback on each.
        void process_chunks(boost::system::error_code ec);
    };

   public:
    /// Uses \p request to create a streaming https connection.
    /** \p actions are used to process each chunk of received data. */
    [[nodiscard]] static auto launch(Request const& request, Callback callback)
        -> Stream;

   private:
    explicit Stream(std::shared_ptr<Stream_impl> ptr);

   public:
    ~Stream();

    Stream(Stream const&) = delete;

    auto operator=(Stream const&) -> Stream& = delete;

   private:
    std::shared_ptr<Stream_impl> ptr_;
};

}  // namespace network
#endif  // NETWORKLIB_STREAM_HPP
