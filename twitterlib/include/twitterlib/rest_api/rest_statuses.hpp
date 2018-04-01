#ifndef TWITTERLIB_REST_API_REST_STATUSES_HPP
#define TWITTERLIB_REST_API_REST_STATUSES_HPP
#include <string>

namespace twitter {
struct App;

void update_status(const App& app, const std::string& message);

}  // namespace twitter
#endif  // TWITTERLIB_REST_API_REST_STATUSES_HPP
