#ifndef TWITTERLIB_OBJECTS_TWEET_HPP
#define TWITTERLIB_OBJECTS_TWEET_HPP
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/coordinates.hpp>
#include <twitterlib/objects/entities.hpp>
#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/place.hpp>

namespace twitter {
struct User_data;

struct Tweet_data {
    explicit operator std::string() const;

    std::vector<std::unique_ptr<Objects_template<User_data>>> contributors;
    Coordinates coordinates;
    std::string created_at;
    std::int64_t current_user_retweet_id;     // current_user_retweet.id
    std::string current_user_retweet_id_str;  // current_user_retweet.id_str
    Entities entities;
    int favorite_count;
    bool favorited;
    std::string filter_level;
    std::int64_t id;
    std::string id_str;
    std::string in_reply_to_screen_name;
    std::int64_t in_reply_to_status_id;
    std::string in_reply_to_status_id_str;
    std::int64_t in_reply_to_user_id;
    std::string in_reply_to_user_id_str;
    std::string lang;
    Place place;
    bool possibly_sensitive;
    std::int64_t quoted_status_id;
    std::string quoted_status_id_str;
    std::unique_ptr<Objects_template<Tweet_data>> quoted_status_ptr;
    std::vector<std::pair<std::string, std::string>> scopes;
    int retweet_count;
    bool retweeted;
    std::unique_ptr<Objects_template<Tweet_data>> retweeted_status_ptr;
    std::string source;
    std::string text;
    bool truncated;
    std::unique_ptr<Objects_template<User_data>> user_ptr;
    bool withheld_copyright;
    std::vector<std::string> withheld_in_countries;
    std::string withheld_scope;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Tweet = Objects_template<Tweet_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_TWEET_HPP
