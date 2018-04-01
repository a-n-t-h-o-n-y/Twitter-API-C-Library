namespace network {
class Request;
}

namespace twitter {
struct App;
namespace detail {

void account_authorize(network::Request& r, const App& app);

void app_only_authorize(network::Request& r, App& app);

}  // namespace detail
}  // namespace twitter
