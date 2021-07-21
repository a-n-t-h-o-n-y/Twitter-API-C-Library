#ifndef NETWORKLIB_DETAIL_SOCKET_STREAM_HPP
#define NETWORKLIB_DETAIL_SOCKET_STREAM_HPP
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/streambuf.hpp>

namespace network::detail {

using Socket_stream = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

using Streambuf = boost::asio::streambuf;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_SOCKET_STREAM_HPP
