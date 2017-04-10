#include "objects/entities.hpp"

#include <string>
#include <sstream>
#include <cstdint>
#include "boost/property_tree/ptree.hpp"
#include "objects/hashtag.hpp"
#include "objects/media.hpp"
#include "objects/url.hpp"
#include "objects/user_mention.hpp"

namespace tal {

Entities_data::operator std::string() const {
    std::stringstream ss;
    ss << "hashtags: ";
    for(const auto& ht : hashtags) {
        ss << '\n' << ht;
    }
    ss << "\n\nmedia: ";
    for(const auto& m : media) {
        ss << '\n' << m;
    }
    ss << "\n\nurls: ";
    for(const auto& url : urls) {
        ss << '\n' << url;
    }
    ss << "\n\nuser_mentions: ";
    for(const auto& um : user_mentions) {
        ss << '\n' << um;
    }
    return ss.str();
}

void Entities_data::construct(const boost::property_tree::ptree& tree) {
    auto hashtags_tree = tree.get_child("hashtags");
    for (auto& pair : hashtags_tree) {
        hashtags.push_back(Hashtag{pair.second});
    }
    auto media_tree = tree.get_child("media");
    for (auto& pair : media_tree) {
        media.push_back(Media{pair.second});
    }
    auto urls_tree = tree.get_child("urls");
    for (auto& pair : urls_tree) {
        urls.push_back(URL{pair.second});
    }
    auto user_mentions_tree = tree.get_child("user_mentions");
    for (auto& pair : user_mentions_tree) {
        user_mentions.push_back(User_mention{pair.second});
    }
}
}  // namespace tal
