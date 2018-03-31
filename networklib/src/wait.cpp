#include <networklib/wait.hpp>

#include <networklib/detail/make_connection.hpp>

namespace network {

void wait() {
    detail::wait_();
}

}  // namespace network
