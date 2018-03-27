#ifndef DETAIL_OAUTH_HPP
#define DETAIL_OAUTH_HPP
#include <string>

#include <networklib/request.hpp>

namespace tal {
namespace detail {

/// Add App and Account OAuth 1.0a header to HTTP request.
// void authorize(Request& request,
//                   const App& app,
//                   const Account& account);

void authorize(Request& request,
               const std::string& consumer_key,
               const std::string& consumer_secret,
               const std::string& access_token,
               const std::string& token_secret);

/// Add App OAuth 2 header to HTTP request.
// void authorize(Request& request, App& app);
// void authorize(Request& request, App& app);

/// Get bearer token from server
// void acquire_bearer_token(App& app);
std::string get_bearer_token(const std::string& consumer_key,
                             const std::string& consumer_secret);

}  // namespace detail
}  // namespace tal

#endif  // DETAIL_OAUTH_HPP
