#ifndef NETWORKLIB_SOCKET_HPP
#define NETWORKLIB_SOCKET_HPP
#include <memory>
#include <string>

#include <boost/asio/ssl/context.hpp>

#include <networklib/detail/io_service.hpp>
#include <networklib/detail/socket_stream.hpp>

namespace network {

/// Move only pointer like access to detail::Socket_stream.
class Socket_old {
   public:
    Socket_old() = delete;

    explicit Socket_old(std::unique_ptr<detail::Socket_stream> contents)
        : socket_ptr_{std::move(contents)}
    {}

   public:
    /// Return reference to underlying detail::Socket_stream.
    [[nodiscard]] auto get() -> detail::Socket_stream& { return *socket_ptr_; }

    /// Return const reference to underlying detail::Socket_stream.
    [[nodiscard]] auto get() const -> detail::Socket_stream const&
    {
        return *socket_ptr_;
    }

    /// Pointer like access to underlying detail::Socket_stream object.
    [[nodiscard]] auto operator->() const -> detail::Socket_stream*
    {
        return socket_ptr_.get();
    }

   private:
    std::unique_ptr<detail::Socket_stream> socket_ptr_ = nullptr;
};

/// Wrapper interface over an SSL TCP Socket.
/** Can only be constructed with a valid connection. If an operation on this
 *  socket object fails an invalidates the object, it should be thrown out.
 *  std::optional is useful to own a potential object of this type. */
class Socket {
   public:
    /// Create a connection to \p host via \p service.
    /** Local hosts are resolved with /etc/hosts, remote hosts with DNS. service
     *  is a name found in /etc/services or a port number. Throws
     *  boost::system::system_error exception if connection cannot be made. */
    [[nodiscard]] static auto make_connection(std::string const& host,
                                              std::string const& service)
        -> Socket;

   public:
    /// Return reference to underlying detail::Socket_stream.
    [[nodiscard]] auto get() -> detail::Socket_stream&;

    /// Return const reference to underlying detail::Socket_stream.
    [[nodiscard]] auto get() const -> detail::Socket_stream const&;

    /// Closes the Socket to reading and writing.
    /** This function should only be used if absolutely necessary. After this
     *  call, *this is no longer valid and should not be used. Used in Stream
     *  destructor because there would be memory issues if the Socket destructor
     *  was relied on to close the connection. Throws
     *  boost::system::system_error if something goes wrong. */
    void close();

   public:
    Socket(Socket&&) = default;

   private:
    explicit Socket(boost::asio::ssl::context ssl_context);

   public:
    ~Socket();

   private:
    detail::Socket_stream socket_stream_;
};

}  // namespace network
#endif  // NETWORKLIB_SOCKET_HPP
