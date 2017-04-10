#include "objects/user.hpp"

#include <string>
#include <sstream>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include "objects/tweet.hpp"
#include "objects/entities.hpp"

namespace tal {

User_data::operator std::string() const {
    std::stringstream ss;
    ss << "contributors_enabled: " << contributors_enabled
       << "created_at: " << created_at
       << "deafult_profile: " << default_profile
       << "default_profile_image: " << default_profile_image
       << "description: " << description
       << "entities: " << entities
       << "favourites_count: " << favourites_count
       << "follow_request_sent: " << follow_request_sent
       << "following: " << following
       << "followers_count: " << followers_count
       << "friends_count: " << friends_count
       << "geo_enabled: " << geo_enabled
       << "id: " << id
       << "id_str: " << id_str
       << "is_translator: " << is_translator
       << "lang: " << lang
       << "listed_count: " << listed_count
       << "location: " << location
       << "name: " << name
       << "notifications: " << notifications
       << "profile_background_color: " << profile_background_color
       << "profile_background_image_url: " << profile_background_image_url
       << "profile_background_image_url_https: " << profile_background_image_url_https
       << "profile_background_tile: " << profile_background_tile
       << "profile_bannder_url: " << profile_bannder_url
       << "profile_image_url: " << profile_image_url
       << "profile_image_url_https: " << profile_image_url_https
       << "profile_link_color: " << profile_link_color
       << "profile_sidebar_border_color: " << profile_sidebar_border_color
       << "profile_text_color: " << profile_text_color
       << "profile_use_background_image: " << profile_use_background_image
       << "protect: " << protect
       << "screen_name: " << screen_name
       << "show_all_inline_media: " << show_all_inline_media
       << "status: " << status
       << "status_count: " << status_count
       << "time_zone: " << time_zone
       << "url: " << url
       << "utc_offset: " << utc_offset
       << "verified: " << verified
       << "withheld_in_countries: " << withheld_in_countries;
    return ss.str();
}

void User_data::construct(const boost::property_tree::ptree& tree) {
    contributors_enabled = tree.get<bool>("contributors_enabled", false);
    created_at = tree.get<std::string>("created_at", "");
    default_profile = tree.get<bool>("default_profile", false);
    default_profile_image = tree.get<bool>("default_profile_image", false);
    description = tree.get<std::string>("description", "");
    entities = Entities{tree.get_child("entities", boost::property_tree::ptree())};
    favourites_count = tree.get<int>("favourites_count", 0);
    follow_request_sent = tree.get<bool>("follow_request_sent", false);
    following = tree.get<bool>("following", false);
    followers_count = tree.get<int>("followers_count", 0);
    friends_count = tree.get<int>("friends_count", 0);
    geo_enabled = tree.get<bool>("geo_enabled", false);
    id = tree.get<std::int64_t>("id", 0);
    id_str = tree.get<std::string>("id_str", "");
    is_translator = tree.get<bool>("is_translator", false);
    lang = tree.get<std::string>("lang", "");
    listed_count = tree.get<int>("listed_count", 0);
    location = tree.get<std::string>("location", "");
    name = tree.get<std::string>("name", "");
    notifications = tree.get<bool>("notifications", false);
    profile_background_color = tree.get<std::string>("profile_background_color", "");
    profile_background_image_url = tree.get<std::string>("profile_background_image_url", "");
    profile_background_image_url_https = tree.get<std::string>("profile_background_image_url_https", "");
    profile_background_tile = tree.get<bool>("profile_background_tile", false);
    profile_bannder_url = tree.get<std::string>("profile_bannder_url", "");
    profile_image_url = tree.get<std::string>("profile_image_url", "");
    profile_image_url_https = tree.get<std::string>("profile_image_url_https", "");
    profile_link_color = tree.get<std::string>("profile_link_color", "");
    profile_sidebar_border_color = tree.get<std::string>("profile_sidebar_border_color", "");
    profile_sidebar_fill_color = tree.get<std::string>("profile_sidebar_fill_color", "");
    profile_text_color = tree.get<std::string>("profile_text_color", "");
    profile_use_background_image = tree.get<bool>("profile_use_background_image", false);
    protect = tree.get<bool>("protected", false);
    screen_name = tree.get<std::string>("screen_name", "");
    show_all_inline_media = tree.get<bool>("show_all_inline_media", false);
    status = Tweet{tree.get_child("status", boost::property_tree::ptree())};
    status_count = tree.get<int>("status_count", 0);
    time_zone = tree.get<std::string>("time_zone", "");
    url = tree.get<std::string>("url", "");
    utc_offset = tree.get<int>("utc_offset", 0);
    verified = tree.get<bool>("verified", false);
    withheld_in_countries = tree.get<std::string>("withheld_in_countries", "");
    withheld_scope = tree.get<std::string>("withheld_scope", "");
}
}  // namespace tal
