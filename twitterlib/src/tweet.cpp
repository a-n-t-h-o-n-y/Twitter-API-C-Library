#include <twitterlib/objects/tweet.hpp>

#include <cstdint>
#include <ios>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/coordinates.hpp>
#include <twitterlib/objects/entities.hpp>
#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/place.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

Tweet_data::operator std::string() const {
    std::stringstream ss;
    ss << std::boolalpha;
    ss << "contributors:\n";
    for (const auto& contributor_ptr : contributors) {
        if (contributor_ptr != nullptr) {
            ss << *contributor_ptr << '\n';
        }
    }
    ss << "coordinates:\n"
       << coordinates << "\ncreated_at: " << created_at
       << "\ncurrent_user_retweet_id: " << current_user_retweet_id
       << "\ncurrent_user_retweet_id_str: " << current_user_retweet_id_str
       << "\nentities:\n"
       << entities << "\nfavorite_count: " << favorite_count
       << "\nfavorited: " << favorited << "\nfilter_level: " << filter_level
       << "\nid: " << id << "\nid_str: " << id_str
       << "\nin_reply_to_screen_name: " << in_reply_to_screen_name
       << "\nin_reply_to_status_id: " << in_reply_to_status_id
       << "\nin_reply_to_status_id_str: " << in_reply_to_status_id_str
       << "\nin_reply_to_user_id: " << in_reply_to_user_id
       << "\nin_reply_to_user_id_str: " << in_reply_to_user_id_str
       << "\nlang: " << lang << "\nplace:\n"
       << place << "\npossibly_sensitive: " << possibly_sensitive
       << "\nquoted_status_id: " << quoted_status_id
       << "\nquoted_status_id_str: " << quoted_status_id_str;
    if (quoted_status_ptr != nullptr) {
        ss << "\nquoted_status:\n" << *quoted_status_ptr;
    }
    ss << "\nscopes:\n";
    for (const auto& pair : scopes) {
        ss << pair.first << ": " << pair.second << '\n';
    }
    ss << "retweet_count: " << retweet_count << "\nretweeted: " << retweeted;
    if (retweeted_status_ptr != nullptr) {
        ss << "\nretweeted_status_ptr:\n" << *retweeted_status_ptr;
    }
    ss << "\nsource: " << source << "\ntext: " << text
       << "\ntruncated: " << truncated;
    if (user_ptr != nullptr) {
        ss << "\nuser:\n" << *user_ptr;
    }
    ss << "\nwithheld_copyright: " << withheld_copyright
       << "\nwithheld_in_countries: ";
    std::string separator{""};
    for (const auto& country : withheld_in_countries) {
        ss << separator << country;
        separator = ", ";
    }
    ss << "\nwithheld_scope: " << withheld_scope;

    return ss.str();
}

void Tweet_data::construct(const boost::property_tree::ptree& tree) {
    auto contributors_tree =
        tree.get_child("contributors", boost::property_tree::ptree());
    for (const auto& pair : contributors_tree) {
        if (!pair.second.empty()) {
            contributors.push_back(std::make_unique<User>(pair.second));
        }
    }
    coordinates = Coordinates{
        tree.get_child("coordinates", boost::property_tree::ptree())};
    created_at = tree.get<std::string>("created_at", "");
    current_user_retweet_id =
        tree.get<std::int64_t>("current_user_retweet.id", -1);
    current_user_retweet_id_str =
        tree.get<std::string>("current_user_retweet.id_str", "");
    entities =
        Entities{tree.get_child("entities", boost::property_tree::ptree())};
    favorite_count = tree.get<int>("favorite_count", -1);
    favorited = tree.get<bool>("favorited", false);
    filter_level = tree.get<std::string>("filter_level", "");
    id = tree.get<std::int64_t>("id", -1);
    id_str = tree.get<std::string>("id_str", "");
    in_reply_to_screen_name =
        tree.get<std::string>("in_reply_to_screen_name", "");
    in_reply_to_status_id = tree.get<std::int64_t>("in_reply_to_status_id", -1);
    in_reply_to_status_id_str =
        tree.get<std::string>("in_reply_to_status_id_str", "");
    in_reply_to_user_id = tree.get<std::int64_t>("in_reply_to_user_id", -1);
    in_reply_to_user_id_str =
        tree.get<std::string>("in_reply_to_user_id_str", "");
    lang = tree.get<std::string>("lang", "");
    place = Place{tree.get_child("place", boost::property_tree::ptree())};
    possibly_sensitive = tree.get<bool>("possibly_sensitive", false);
    quoted_status_id = tree.get<std::int64_t>("quoted_status_id", -1);
    quoted_status_id_str = tree.get<std::string>("quoted_status_id_str", "");
    auto quoted_status_tree =
        tree.get_child("quoted_status", boost::property_tree::ptree());
    if (!quoted_status_tree.empty()) {
        quoted_status_ptr = std::make_unique<Tweet>(quoted_status_tree);
    }
    auto scopes_tree = tree.get_child("scopes", boost::property_tree::ptree());
    for (const auto& pair : scopes_tree) {
        scopes.push_back(
            std::make_pair(pair.first, pair.second.get_value<std::string>("")));
    }
    retweet_count = tree.get<int>("retweet_count", -1);
    retweeted = tree.get<bool>("retweeted", false);
    auto retweeted_status_tree =
        tree.get_child("retweeted_status", boost::property_tree::ptree());
    if (!retweeted_status_tree.empty()) {
        retweeted_status_ptr = std::make_unique<Tweet>(retweeted_status_tree);
    }
    source = tree.get<std::string>("source", "");
    text = tree.get<std::string>("text", "");
    truncated = tree.get<bool>("truncated", false);
    auto user_tree = tree.get_child("user", boost::property_tree::ptree());
    if (!user_tree.empty()) {
        user_ptr = std::make_unique<User>(user_tree);
    }
    withheld_copyright = tree.get<bool>("withheld_copyright", false);
    auto wic_tree =
        tree.get_child("withheld_in_countries", boost::property_tree::ptree());
    for (const auto& pair : wic_tree) {
        withheld_in_countries.push_back(pair.first);
    }
    withheld_scope = tree.get<std::string>("withheld_scope", "");
}

}  // namespace twitter
