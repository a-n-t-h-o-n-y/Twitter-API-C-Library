#include <twitterlib/objects/url.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace twitter {

URL_data::operator std::string() const {
    std::stringstream ss;
    ss << "display_url: " << display_url << "\nexpanded_url: " << expanded_url
       << "\nurl: " << url << "\nindices: " << indices[0] << ", " << indices[1];
    return ss.str();
}

void URL_data::construct(const boost::property_tree::ptree& tree) {
    display_url = tree.get<std::string>("display_url", "");
    expanded_url = tree.get<std::string>("expanded_url", "");
    url = tree.get<std::string>("url", "");
    auto indices_tree =
        tree.get_child("indices", boost::property_tree::ptree());
    int count{0};
    for (auto& pair : indices_tree) {
        indices[count++] = pair.second.get_value<int>(-1);
    }
}

}  // namespace twitter
