#include "objects/user_mention.hpp"

#include <string>
#include <sstream>
#include <cstdint>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

namespace tal {

User_mention::User_mention(const std::string& json) {
    boost::property_tree::ptree tree;
    std::istringstream ss(json);
    boost::property_tree::read_json(ss, tree);
    this->construct(tree);
}

User_mention::User_mention(const boost::property_tree::ptree& tree) {
    this->construct(tree);
}

void User_mention::construct(const boost::property_tree::ptree& tree) {
    id = tree.get<std::int64_t>("id");
    id_str= tree.get<std::string>("id_str");
    auto indices_tree = tree.get_child("indices");
    int count{0};
    for (auto& pair : indices_tree) {
        indices[count++] = pair.second.get_value<int>();
    }
    name = tree.get<std::string>("name");
    screen_name = tree.get<std::string>("screen_name");
}
}  // namespace tal
