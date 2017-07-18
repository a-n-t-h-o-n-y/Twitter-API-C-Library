#ifndef DETAIL_TYPES_HPP
#define DETAIL_TYPES_HPP

#include <cstdint>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tal {

using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;
using twitter_id = std::int64_t;

struct coordinates {
    float lattitude;
    float longitude;
};

} // namespace tal

#endif // DETAIL_TYPES_HPP
