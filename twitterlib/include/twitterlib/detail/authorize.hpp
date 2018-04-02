#ifndef TWITTERLIB_DETAIL_AUTHORIZE_HPP
#define TWITTERLIB_DETAIL_AUTHORIZE_HPP
namespace network {
class Request;
}  // namespace network

namespace twitter {
struct App;
namespace detail {

void account_authorize(network::Request& r, const App& app);

void app_only_authorize(network::Request& r, App& app);

}  // namespace detail
}  // namespace twitter
#endif  // TWITTERLIB_DETAIL_AUTHORIZE_HPP
