#ifndef NETWORKLIB_DETAIL_SOCKET_HPP
#define NETWORKLIB_DETAIL_SOCKET_HPP
#include <memory>

#include <networklib/detail/socket_stream.hpp>

namespace network {
namespace detail {

struct Socket {
    std::unique_ptr<Socket_stream> socket_ptr{nullptr};
};

}  // namespace detail
}  // namespace network
#endif  // NETWORKLIB_DETAIL_SOCKET_HPP
