#ifndef NETWORKLIB_DETAIL_SOCKET_HPP
#define NETWORKLIB_DETAIL_SOCKET_HPP
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace network {
namespace detail {

struct Socket {
    std::unique_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>
        socket_ptr{nullptr};
};

}  // namespace detail
}  // namespace network

#endif  // NETWORKLIB_DETAIL_SOCKET_HPP
