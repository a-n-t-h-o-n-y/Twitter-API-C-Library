#ifndef TWITTERLIB_OBJECTS_USER_HPP
#define TWITTERLIB_OBJECTS_USER_HPP
#include <cstdint>
#include <memory>
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/entities.hpp>
#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/tweet.hpp>

namespace twitter {

struct User_data {
    explicit operator std::string() const;

    bool contributors_enabled;
    std::string created_at;
    bool default_profile;
    bool default_profile_image;
    std::string description;
    Entities entities;
    int favourites_count;
    bool follow_request_sent;
    bool following;
    int followers_count;
    int friends_count;
    bool geo_enabled;
    std::int64_t id;
    std::string id_str;
    bool is_translator;
    std::string lang;
    int listed_count;
    std::string location;
    std::string name;
    bool notifications;
    std::string profile_background_color;
    std::string profile_background_image_url;
    std::string profile_background_image_url_https;
    bool profile_background_tile;
    std::string profile_bannder_url;
    std::string profile_image_url;
    std::string profile_image_url_https;
    std::string profile_link_color;
    std::string profile_sidebar_border_color;
    std::string profile_sidebar_fill_color;
    std::string profile_text_color;
    bool profile_use_background_image;
    bool protect;  // -ed
    std::string screen_name;
    bool show_all_inline_media;
    Tweet status;
    int statuses_count;
    std::string time_zone;
    std::string url;
    int utc_offset;
    bool verified;
    std::string withheld_in_countries;
    std::string withheld_scope;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using User = Objects_template<User_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_USER_HPP
