#ifndef TWITTERLIB_REST_STATUSES_HPP
#define TWITTERLIB_REST_STATUSES_HPP
#include <string>

#include <oauth/credentials.hpp>

namespace twitter {

void update_status(oauth::Credentials const& app, std::string const& message);

}  // namespace twitter
#endif  // TWITTERLIB_REST_STATUSES_HPP
