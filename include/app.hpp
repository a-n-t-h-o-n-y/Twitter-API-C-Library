#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <vector>

#include "account.hpp"
#include "response.hpp"
#include "stream.hpp"

namespace tal {
class Account;
class Request;

class App {
   public:
    /// Set the consumer key and consumer secret at construction.
    App(const std::string& key, const std::string& secret)
        : consumer_key_{key}, consumer_secret_{secret} {};

    void set_account(const Account& account);

    /// Returns consumer key.
    std::string key() const { return consumer_key_; }

    /// Returns consumer secret.
    std::string secret() const { return consumer_secret_; }

    /// Set consumer key.
    void set_key(const std::string& key) { consumer_key_ = key; }

    /// Set consumer secret.
    void set_secret(const std::string& secret) { consumer_secret_ = secret; }

    /// Get bearer token from server
    void acquire_bearer_token();

    /// Return bearer token.
    std::string bearer_token() const { return bearer_token_; }

    // Twitter Functions
    void update_status(const std::string& message);

    void contact_google();

   private:
    std::string consumer_key_;
    std::string consumer_secret_;
    std::string bearer_token_;
    User_stream user_stream_(this);
    Public_stream filtered_stream_(this, "/1.1/statuses/filter.json", "POST");
    Public_stream sample_stream_(this, "/1.1/statuses/sample.json", "GET");

    // Every request through this app will send to these accounts, is there a
    // use case for multiple accounts?
    Account account_;

    // These two functions are used by each public method above.
    // Sends the request off to the account with the proper oauth header created
    // and inserted into the original request.
    Response send(const Request& request, const Account& account);
    // sends an application authentication only request
    Response send(const Request& request);
};
}

#endif  // APP_HPP
