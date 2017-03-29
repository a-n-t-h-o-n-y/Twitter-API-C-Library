#ifndef OAUTH_HPP
#define OAUTH_HPP

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

}  // namespace detail
}  // namespace tal

#endif  // OAUTH_HPP
