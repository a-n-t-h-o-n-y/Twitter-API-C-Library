#ifndef TWITTERLIB_APP_HPP
#define TWITTERLIB_APP_HPP
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include <networklib/response.hpp>

#include <twitterlib/account.hpp>
#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/user.hpp>
#include <twitterlib/twitter_stream.hpp>

namespace network {
class Request;
}

namespace twitter {

struct App {
    /// Set the consumer key and consumer secret at construction.
    App(std::string key, std::string secret)
        : consumer_key{std::move(key)}, consumer_secret{std::move(secret)} {}

    std::string consumer_key;
    std::string consumer_secret;
    std::string bearer_token;

    Account account;

    Twitter_stream user_stream{this, build_user_stream_parameters()};
    Twitter_stream filtered_stream{this, build_filtered_stream_parameters()};
    Twitter_stream sample_stream{this, build_sample_stream_parameters()};

    ////////////////////////////////////////////////////////////////////////////
    // - - - REST API - - -
    // void update_status(const std::string& message);

    // network::Response verify_credentials(bool include_entities = true,
    //                                      bool skip_status = false,
    //                                      bool include_email = false);

    // std::vector<std::int64_t> get_blocked_ids();

    // std::vector<User> get_blocked_users(bool include_entities = false,
    //                                     bool skip_status = true);

    // // TODO: Change return type to Colletion, that wraps a vector<Tweet> and
    // // includes the description data as well.
    // network::Response get_collection(const std::string& id,
    //                                  int count = -1,
    //                                  int max_position = -1,
    //                                  int min_position = -1);

    // network::Response find_collections(const std::string& screen_name,
    //                                    std::int64_t user_id = -1,
    //                                    std::int64_t tweet_id = -1,
    //                                    int count = -1);

    // network::Response get_collection_info(const std::string& id);


    // network::Response get_application_rate_limit_status();

    // network::Response get_account_rate_limit_status();
};

}  // namespace twitter
#endif  // TWITTERLIB_APP_HPP
