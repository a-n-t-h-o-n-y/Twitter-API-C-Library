#ifndef TWITTERLIB_OBJECTS_TWEET_HPP
#define TWITTERLIB_OBJECTS_TWEET_HPP
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/coordinates.hpp>
#include <twitterlib/objects/entities.hpp>
#include <twitterlib/objects/place.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

struct Tweet {
    std::string created_at;
    std::int64_t id;
    std::string text;
    std::string source;
    bool truncated;
    std::optional<std::int64_t> in_reply_to_status_id;
    std::optional<std::int64_t> in_reply_to_user_id;
    std::optional<std::string> in_reply_to_screen_name;
    User user;
    std::optional<Coordinates> coordinates;
    std::optional<Place> place;
    std::optional<std::int64_t> quoted_status_id;
    bool is_quote_status;
    std::unique_ptr<Tweet> quoted_status;
    std::unique_ptr<Tweet> retweeted_status;
    int retweet_count;
    int favorite_count;
    Entities entities;
    std::optional<bool> favorited;
    std::optional<bool> retweeted;
    std::optional<bool> possibly_sensitive;
    std::string filter_level;
    std::optional<std::string> lang;
    std::optional<std::int64_t> current_user_retweet_id;
    bool withheld_copyright;
    std::vector<std::string> withheld_in_countries;
    std::string withheld_scope;
};

/// Generates a string display of all data in \p tweet.
[[nodiscard]] auto to_string(Tweet const& tweet) -> std::string;

/// Create a Tweet from a property tree.
[[nodiscard]] auto parse_tweet(boost::property_tree::ptree const& tree)
    -> Tweet;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_TWEET_HPP
