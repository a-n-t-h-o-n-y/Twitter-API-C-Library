#ifndef DETAIL_OAUTH_HPP
#define DETAIL_OAUTH_HPP

#include <string>

#include "../request.hpp"

namespace tal {
class App;
class Account;

namespace detail {

/// Add App and Account OAuth 1.0a header to HTTP request.
void authorize(Request& request,
                  const App& app,
                  const Account& account);

/// Add App OAuth 1.0a header to HTTP request.
void authorize(Request& request, App& app);

/// Get bearer token from server
void acquire_bearer_token(App& app);

}  // namespace detail
}  // namespace tal

#endif  // DETAIL_OAUTH_HPP
