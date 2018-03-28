#include <twitterlib/objects/hashtag.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace twitter {

Hashtag_data::operator std::string() const {
    std::stringstream ss;
    ss << "text: " << text << "\nindices: " << indices[0] << ", " << indices[1];
    return ss.str();
}

void Hashtag_data::construct(const boost::property_tree::ptree& tree) {
    text = tree.get<std::string>("text", "");
    auto indices_tree =
        tree.get_child("indices", boost::property_tree::ptree());
    int count{0};
    for (auto& pair : indices_tree) {
        indices[count++] = pair.second.get_value<int>(-1);
    }
}

}  // namespace twitter
