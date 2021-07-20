#include <networklib/wait.hpp>

#include <networklib/detail/io_service.hpp>

namespace network {

void wait() { detail::io_service().run(); }

}  // namespace network
