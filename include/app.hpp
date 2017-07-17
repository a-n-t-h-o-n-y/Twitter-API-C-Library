#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <boost/asio.hpp>
#include "account.hpp"
#include "stream.hpp"
#include "message.hpp"
#include "objects/tweet.hpp"
#include "objects/user.hpp"
#include "objects/place.hpp"

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

    void update_status(const std::string& message);
    // REST API
    Message get_account_settings();

    Message verify_credentials(bool include_entities = true,
                            bool skip_status = false,
                            bool include_email = false);

    // Implement cursoring and interface that makes sense for that.
    // It's easy
    std::vector<std::int64_t> get_blocked_ids(std::int64_t cursor = -1);

    std::vector<User> get_blocked_users(bool include_entities = false,
                                        bool skip_status = true,
                                        std::int64_t cursor = -1);

    // Change return type to Colletion, that wraps a vector<Tweet> and
    // includes the description data as well.
    std::vector<Tweet> get_collection(const std::string& id,
                                      int count = -1,
                                      int max_position = -1,
                                      int min_position = -1);

    // response is under the response.results array of string ids for
    // collections/timelines
    std::vector<std::string> get_users_collections(
        const std::string& screen_name,
        std::int64_t user_id = -1,
        std::int64_t tweet_id = -1,
        int count = -1,
        std::string cursor = "");

    // Return a Collection object with no tweets? or just a Collection_metadata
    // object, that would be better
    Message get_collection_metadata(const std::string& id);

    // Create a Direct_message object, return a vector of DMs
    Message get_direct_messages(std::int64_t since_id = -1,
                                std::int64_t max_id = -1,
                                int count = -1,
                                bool include_entities = false,
                                bool skip_status = true);

    // Return a Direct_message
    Message get_direct_message(std::int64_t id);

    // Return vector<Direct_message> also what happened to skip_status? can you
    // still send it? did the twitter documentation leave it out on accident?
    Message get_sent_direct_messages(std::int64_t since_id = -1,
                                     std::int64_t max_id = -1,
                                     int count = -1,
                                     int page = -1,
                                     bool include_entities = false);

    // Create a direct_message_event class, return a vector of them.
    Message get_direct_message_events(int count = -1,
                                      const std::string cursor = "");

    // Return a Direct_message_event
    Message get_direct_message_event(std::int64_t id);

    // Return a vector of Welcome_message type
    Message get_welcome_messages(int count = -1,
                                 const std::string& cursor = "");

    // Return a vector of Welcome_message_rule type
    Message get_welcome_message_rules(int count = -1,
                                      const std::string& cursor = "");

    // Return a Welcome_message_rule type
    Message get_welcome_message_rule(std::int64_t id);

    // Return a Welcome_message type
    Message get_welcome_message(std::int64_t id);

    /// Use -1 or empty string for a value you do not wish to specify.
    std::vector<Tweet> get_favorites(const std::string& screen_name,
                                     int count = -1,
                                     bool include_entities = false,
                                     std::int64_t user_id = -1,
                                     std::int64_t since_id = -1,
                                     std::int64_t max_id = -1);

    //
    std::vector<std::int64_t> get_follower_ids(
        const std::string& screen_name = "",
        std::int64_t user_id = -1,
        int count = -1,
        std::int64_t cursor = 0);

    //
    std::vector<User> get_followers(const std::string& screen_name = "",
                                    std::int64_t id = -1,
                                    int count = -1,
                                    bool skip_status = true,
                                    bool include_entities = false,
                                    std::int64_t cursor = 0);

    //
    std::vector<std::int64_t> get_friend_ids(
        const std::string& screen_name = "",
        std::int64_t user_id = -1,
        int count = -1,
        std::int64_t cursor = 0);

    //
    std::vector<User> get_friends(const std::string& screen_name = "",
                                  std::int64_t user_id = -1,
                                  int count = -1,
                                  bool skip_status = true,
                                  bool include_entities = false,
                                  std::int64_t cursor = 0);

    // Returns ids of users that have pending friendship requests to the
    // authenticating user
    std::vector<std::int64_t> get_incoming_friendships(std::int64_t cursor = 0);

    // Return a vector of Relationship type, comma seperated list of up to 100
    // names/ids
    Message get_relationships(const std::string& screen_names = "",
                              const std::vector<std::int64_t>& user_ids =
                                  std::vector<std::int64_t>());

    // Returns a list of ids of users the authenticating user does not want to
    // see retweets from.
    std::vector<std::int64_t> get_no_retweet_ids();

    // Returns user ids of pending requests the authenticating user has sent.
    std::vector<std::int64_t> get_pending_friendships(std::int64_t cursor = 0);

    // Returns a Relationship object that may be different from the previous
    // Relationship type? hope to make them the same type or differentiate them
    Message get_relationship(const std::string& source_screen_name = "",
                             const std::string& target_screen_name = "",
                             std::int64_t source_user_id = -1,
                             std::int64_t target_user_id = -1);

    // Return a Place type, may have to extend Place class from what it
    // currently is
    Place get_place(const std::string& id);

    // Returns a list of Places near lat and lon
    std::vector<Place> get_places_near(
        float latitude = -1,
        float longitude = -1,
        const std::string& query = "",
        const std::string& ip = "",
        const std::string& accuracy = "",
        const std::string& granularity = "",
        int max_results = -1,
        const std::string& contained_within = "",  // attribute:street_address
        const std::string& street_address = "",
        const std::string& callback = "");

    // Maybe make a class for this?
    Message get_configuration();

    //
    Message get_languages();

    //
    Message get_privacy_policy();

    //
    Message get_tos();

    // Returns a List object, which a user subscribes to, create this class
    Message get_lists(const std::string& screen_name = "",
                      std::int64_t user_id = -1,
                      bool reverse = false);

    //
    std::vector<User> get_list_members(
        std::int64_t list_id = -1,
        const std::string& slug = "",
        const std::string& owner_screen_name = "",
        int count = -1,
        bool include_entities = false,
        bool skip_status = true,
        std::int64_t cursor = 0);

    // not sure what this returns, a User?
    Message check_list_membership(std::int64_t list_id = -1,
                                  const std::string& slug = "",
                                  std::int64_t user_id = -1,
                                  const std::string& scren_name = "",
                                  const std::string& owner_screen_name = "",
                                  bool include_entities = false,
                                  bool skip_status = true);

    // vector of lists, is this the same as get_lists?
    Message get_lists_added_to(std::int64_t user_id = -1,
                               const std::string& screen_name = "",
                               int count = -1,
                               bool filter_to_owned_lists = false,
                               std::int64_t cursor = 0);

    //
    Message get_owned_lists(std::int64_t user_id = -1,
                            const std::string& screen_name = "",
                            int count = -1,
                            std::int64_t cursor = 0);

    //
    Message get_list(std::int64_t list_id = -1,
                     const std::string& slug = "",
                     const std::string& owner_screen_name = "",
                     std::int64_t owner_id = -1);
    //
    std::vector<Tweet> get_list_statuses(
        std::int64_t list_id = -1,
        const std::string& slug = "",
        const std::string& owner_screen_name = "",
        std::int64_t owner_id = -1,
        std::int64_t since_id = -1,
        std::int64_t max_id = -1,
        int count = -1,
        bool include_entities = false,
        bool include_retweets = true);

    Message get_application_rate_limit_status();

    Message get_account_rate_limit_status();

    ////////////////////////////////////////////////////////////////////////////

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
