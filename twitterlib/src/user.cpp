#include <twitterlib/objects/user.hpp>

#include <cstdint>
#include <ios>
#include <memory>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/entities.hpp>
#include <twitterlib/objects/tweet.hpp>

namespace twitter {

User_data::operator std::string() const {
    std::stringstream ss;
    ss << std::boolalpha;
    ss << "contributors_enabled: " << contributors_enabled
       << "\ncreated_at: " << created_at
       << "\ndefault_profile: " << default_profile
       << "\ndefault_profile_image: " << default_profile_image
       << "\ndescription: " << description << "\nentities:\n"
       << entities << "\nfavourites_count: " << favourites_count
       << "\nfollow_request_sent: " << follow_request_sent
       << "\nfollowing: " << following
       << "\nfollowers_count: " << followers_count
       << "\nfriends_count: " << friends_count
       << "\ngeo_enabled: " << geo_enabled << "\nid: " << id
       << "\nid_str: " << id_str << "\nis_translator: " << is_translator
       << "\nlang: " << lang << "\nlisted_count: " << listed_count
       << "\nlocation: " << location << "\nname: " << name
       << "\nnotifications: " << notifications
       << "\nprofile_background_color: " << profile_background_color
       << "\nprofile_background_image_url: " << profile_background_image_url
       << "\nprofile_background_image_url_https: "
       << profile_background_image_url_https
       << "\nprofile_background_tile: " << profile_background_tile
       << "\nprofile_bannder_url: " << profile_bannder_url
       << "\nprofile_image_url: " << profile_image_url
       << "\nprofile_image_url_https: " << profile_image_url_https
       << "\nprofile_link_color: " << profile_link_color
       << "\nprofile_sidebar_border_color: " << profile_sidebar_border_color
       << "\nprofile_text_color: " << profile_text_color
       << "\nprofile_use_background_image: " << profile_use_background_image
       << "\nprotect: " << protect << "\nscreen_name: " << screen_name
       << "\nshow_all_inline_media: " << show_all_inline_media << "\nstatus:\n"
       << status << "\nstatuses_count: " << statuses_count
       << "\ntime_zone: " << time_zone << "\nurl: " << url
       << "\nutc_offset: " << utc_offset << "\nverified: " << verified
       << "\nwithheld_in_countries: " << withheld_in_countries;
    return ss.str();
}

void User_data::construct(const boost::property_tree::ptree& tree) {
    contributors_enabled = tree.get<bool>("contributors_enabled", false);
    created_at = tree.get<std::string>("created_at", "");
    default_profile = tree.get<bool>("default_profile", false);
    default_profile_image = tree.get<bool>("default_profile_image", false);
    description = tree.get<std::string>("description", "");
    entities =
        Entities{tree.get_child("entities", boost::property_tree::ptree())};
    favourites_count = tree.get<int>("favourites_count", -1);
    follow_request_sent = tree.get<bool>("follow_request_sent", false);
    following = tree.get<bool>("following", false);
    followers_count = tree.get<int>("followers_count", -1);
    friends_count = tree.get<int>("friends_count", -1);
    geo_enabled = tree.get<bool>("geo_enabled", false);
    id = tree.get<std::int64_t>("id", -1);
    id_str = tree.get<std::string>("id_str", "");
    is_translator = tree.get<bool>("is_translator", false);
    lang = tree.get<std::string>("lang", "");
    listed_count = tree.get<int>("listed_count", -1);
    location = tree.get<std::string>("location", "");
    name = tree.get<std::string>("name", "");
    notifications = tree.get<bool>("notifications", false);
    profile_background_color =
        tree.get<std::string>("profile_background_color", "");
    profile_background_image_url =
        tree.get<std::string>("profile_background_image_url", "");
    profile_background_image_url_https =
        tree.get<std::string>("profile_background_image_url_https", "");
    profile_background_tile = tree.get<bool>("profile_background_tile", false);
    profile_bannder_url = tree.get<std::string>("profile_bannder_url", "");
    profile_image_url = tree.get<std::string>("profile_image_url", "");
    profile_image_url_https =
        tree.get<std::string>("profile_image_url_https", "");
    profile_link_color = tree.get<std::string>("profile_link_color", "");
    profile_sidebar_border_color =
        tree.get<std::string>("profile_sidebar_border_color", "");
    profile_sidebar_fill_color =
        tree.get<std::string>("profile_sidebar_fill_color", "");
    profile_text_color = tree.get<std::string>("profile_text_color", "");
    profile_use_background_image =
        tree.get<bool>("profile_use_background_image", false);
    protect = tree.get<bool>("protected", false);
    screen_name = tree.get<std::string>("screen_name", "");
    show_all_inline_media = tree.get<bool>("show_all_inline_media", false);
    status = Tweet{tree.get_child("status", boost::property_tree::ptree())};
    statuses_count = tree.get<int>("statuses_count", -1);
    time_zone = tree.get<std::string>("time_zone", "");
    url = tree.get<std::string>("url", "");
    utc_offset = tree.get<int>("utc_offset", -1);
    verified = tree.get<bool>("verified", false);
    withheld_in_countries = tree.get<std::string>("withheld_in_countries", "");
    withheld_scope = tree.get<std::string>("withheld_scope", "");
}

}  // namespace twitter
