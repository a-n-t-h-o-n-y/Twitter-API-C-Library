#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tal {

using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;
using twitter_id = std::int64_t;

} // namespace tal

#endif // TYPES_HPP
