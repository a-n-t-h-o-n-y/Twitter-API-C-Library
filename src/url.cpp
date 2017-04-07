#include "objects/url.hpp"

#include <string>
#include <sstream>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

namespace tal {

URL::URL(const std::string& json) {
    boost::property_tree::ptree tree;
    std::istringstream ss(json);
    boost::property_tree::read_json(ss, tree);
    this->construct(tree);
}

URL::URL(const boost::property_tree::ptree& tree) {
    this->construct(tree);
}

void URL::construct(const boost::property_tree::ptree& tree) {
    display_url = tree.get<std::string>("display_url");
    expanded_url = tree.get<std::string>("expanded_url");
    url = tree.get<std::string>("url");
    auto indices_tree = tree.get_child("indices");
    int count{0};
    for (auto& pair : indices_tree) {
        indices[count++] = pair.second.get_value<int>();
    }
}

}  // namespace tal
