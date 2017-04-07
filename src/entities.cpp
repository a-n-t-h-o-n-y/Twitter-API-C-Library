#include "objects/entities.hpp"

#include <string>
#include <sstream>
#include <cstdint>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "objects/hashtag.hpp"
#include "objects/media.hpp"
#include "objects/url.hpp"
#include "objects/user_mention.hpp"

namespace tal {

Entities::Entities(const std::string& json) {
    boost::property_tree::ptree tree;
    std::istringstream ss(json);
    boost::property_tree::read_json(ss, tree);
    this->construct(tree);
}

Entities::Entities(const boost::property_tree::ptree& tree) {
    this->construct(tree);
}

Entities::operator std::string() const {
    std::stringstream ss;
    // fill in
    return ss.str();
}

void Entities::construct(const boost::property_tree::ptree& tree) {
    auto hashtags_tree = tree.get_child("hashtags");
    for (auto& pair : hashtags_tree) {
        hashtags.push_back(Hashtag(pair.second));
    }
    // repeat etc..
    // std::vector<Media> media;
    // std::vector<URL> urls;
    // std::vector<User_mention> user_mentions;
}
}  // namespace tal
