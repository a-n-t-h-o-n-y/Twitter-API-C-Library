#ifndef OAUTH_AUTHORIZE_HPP
#define OAUTH_AUTHORIZE_HPP
#include <oauth/credentials.hpp>

namespace network {
struct Request;
}  // namespace network

namespace oauth {

/// Add App and Account OAuth 1.0a header to HTTP request.
void authorize(network::Request& request, Credentials const& keys);

}  // namespace oauth
#endif  // OAUTH_AUTHORIZE_HPP
