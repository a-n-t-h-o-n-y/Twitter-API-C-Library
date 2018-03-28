#include <twitterlib/objects/entities.hpp>

#include <cstdint>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/hashtag.hpp>
#include <twitterlib/objects/media.hpp>
#include <twitterlib/objects/url.hpp>
#include <twitterlib/objects/user_mention.hpp>

namespace twitter {

Entities_data::operator std::string() const {
    std::stringstream ss;
    ss << "hashtags:";
    for (const auto& ht : hashtags) {
        ss << "\n" << ht;
    }
    ss << "\nmedia: ";
    for (const auto& m : media) {
        ss << "\n" << m;
    }
    ss << "\nurls: ";
    for (const auto& url : urls) {
        ss << "\n" << url;
    }
    ss << "\nuser_mentions: ";
    for (const auto& um : user_mentions) {
        ss << "\n" << um;
    }
    return ss.str();
}

void Entities_data::construct(const boost::property_tree::ptree& tree) {
    auto hashtags_tree =
        tree.get_child("hashtags", boost::property_tree::ptree());
    for (auto& pair : hashtags_tree) {
        hashtags.push_back(Hashtag{pair.second});
    }
    auto media_tree = tree.get_child("media", boost::property_tree::ptree());
    for (auto& pair : media_tree) {
        media.push_back(Media{pair.second});
    }
    auto urls_tree = tree.get_child("urls", boost::property_tree::ptree());
    for (auto& pair : urls_tree) {
        urls.push_back(URL{pair.second});
    }
    auto user_mentions_tree =
        tree.get_child("user_mentions", boost::property_tree::ptree());
    for (auto& pair : user_mentions_tree) {
        user_mentions.push_back(User_mention{pair.second});
    }
}

}  // namespace twitter
