#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "../response.hpp"

namespace tal {
class Request;
namespace detail {

/// Creates a connection and sends a fully formed response to the endpoint.
/// \returns HTTP response from the endpoint.
Response send_HTTP(const Request& request);

/// Throws exception if HTTP resonse is not 200.
void digest(const Response& response);

}  // namespace detail
}  // namespace tal

#endif  // NETWORK_HPP
