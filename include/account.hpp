#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include <utility>

namespace tal {

/// Represets a Twitter account, with access token and secret.
class Account {
   public:
    Account() = default;
    /// Set the token and token secret at construction.
    Account(std::string token, std::string secret)
        : token_{std::move(token)}, token_secret_{std::move(secret)} {}

    Account(const Account&) = default;

    /// returns the token.
    std::string token() const { return token_; }

    /// Returns the token secret.
    std::string secret() const { return token_secret_; }

    /// Set the token.
    void set_token(const std::string& token) { token_ = token; }

    /// Set the token secret.
    void set_secret(const std::string& secret) { token_secret_ = secret; }

   private:
    std::string token_;
    std::string token_secret_;
};

}  // namespace tal

#endif  // ACCOUNT_HPP
