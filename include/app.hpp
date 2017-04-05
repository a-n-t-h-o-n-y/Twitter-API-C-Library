#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <vector>

#include "account.hpp"
#include "stream.hpp"
#include "message.hpp"

#include <boost/asio.hpp>

namespace tal {
class Account;
class Request;

class App {
   public:
    /// Set the consumer key and consumer secret at construction.
    App(const std::string& key, const std::string& secret)
        : consumer_key_{key}, consumer_secret_{secret} {}

    ~App() { ios_ptr_->run(); }

    void set_account(const Account& account);

    /// Returns consumer key.
    std::string key() const { return consumer_key_; }

    /// Returns consumer secret.
    std::string secret() const { return consumer_secret_; }

    /// Set consumer key.
    void set_key(const std::string& key) { consumer_key_ = key; }

    /// Set consumer secret.
    void set_secret(const std::string& secret) { consumer_secret_ = secret; }

    /// Return bearer token.
    std::string bearer_token() const { return bearer_token_; }

    /// Set bearer token value.
    void set_bearer_token(std::string token) {
        bearer_token_ = std::move(token);
    }

    boost::asio::io_service& io_service() { return *ios_ptr_; }

    /// Get account associated with this App object.
    Account account() const { return account_; }

    // Twitter Functions
    void update_status(const std::string& message);

    void verify_credentials();

    void get_favorites(const std::string& user);

    // Streams
    void register_to_user_stream(Stream::Callback callback,
                                 Stream::Condition condition =
                                     [](const Message&) { return true; });
    void register_to_filtered_stream(Stream::Callback callback,
                                     Stream::Condition condition =
                                         [](const Message&) { return true; });

    void register_to_sample_stream(Stream::Callback callback,
                                   Stream::Condition condition =
                                       [](const Message&) { return true; });
    Public_stream& filtered_stream() { return filtered_stream_; }

   private:
    std::unique_ptr<boost::asio::io_service> ios_ptr_{
        std::make_unique<boost::asio::io_service>()};
    std::string consumer_key_;
    std::string consumer_secret_;
    std::string bearer_token_;
    User_stream user_stream_{this};
    Public_stream filtered_stream_{this, "/1.1/statuses/filter.json", "POST"};
    Public_stream sample_stream_{this, "/1.1/statuses/sample.json", "GET"};

    // Every request through this app will send to these accounts, is there a
    // use case for multiple accounts?
    Account account_;

    // These two functions are used by each public method above.
    // Sends the request off to the account with the proper oauth header created
    // and inserted into the original request.
    Message send(Request& request, const Account& account);
    // sends an application authentication only request
    Message send(Request& request);
};
}

#endif  // APP_HPP
