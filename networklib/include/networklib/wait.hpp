#ifndef NETWORKLIB_WAIT_HPP
#define NETWORKLIB_WAIT_HPP

namespace network {

// Waits on the io_service object until there is no more work to do.
void wait();

}  // namespace network
#endif  // NETWORKLIB_WAIT_HPP
