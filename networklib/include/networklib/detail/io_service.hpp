#ifndef NETWORKLIB_DETAIL_IO_SERVICE_HPP
#define NETWORKLIB_DETAIL_IO_SERVICE_HPP
#include <boost/asio/io_service.hpp>

namespace network::detail {

[[nodiscard]] inline auto io_service() -> boost::asio::io_service&
{
    static auto io_s = boost::asio::io_service{};
    return io_s;
}

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_IO_SERVICE_HPP
