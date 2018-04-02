#ifndef TWITTERLIB_ACCOUNT_HPP
#define TWITTERLIB_ACCOUNT_HPP
#include <string>

namespace twitter {

/// Holds Twitter account credentials.
struct Account {
    std::string token;
    std::string secret;
};

}  // namespace twitter
#endif  // TWITTERLIB_ACCOUNT_HPP
