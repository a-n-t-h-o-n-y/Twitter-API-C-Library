#include <twitterlib/objects/user_mention.hpp>

#include <cstdint>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace twitter {

User_mention_data::operator std::string() const {
    std::stringstream ss;
    ss << "id: " << id << "\nid_str: " << id_str << "\nindices: " << indices[0]
       << ", " << indices[1] << "\nname: " << name
       << "\nscreen_name: " << screen_name;
    return ss.str();
}

void User_mention_data::construct(const boost::property_tree::ptree& tree) {
    id = tree.get<std::int64_t>("id", -1);
    id_str = tree.get<std::string>("id_str", "");
    auto indices_tree =
        tree.get_child("indices", boost::property_tree::ptree());
    int count{0};
    for (auto& pair : indices_tree) {
        indices[count++] = pair.second.get_value<int>(-1);
    }
    name = tree.get<std::string>("name", "");
    screen_name = tree.get<std::string>("screen_name", "");
}

}  // namespace twitter
