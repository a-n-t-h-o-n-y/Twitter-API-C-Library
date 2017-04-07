#include "objects/hashtag.hpp"

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace tal {

Hashtag::Hashtag(const std::string& json) {
    boost::property_tree::ptree tree;
    std::istringstream ss(json);
    boost::property_tree::read_json(ss, tree);
    this->construct(tree);
}

Hashtag::Hashtag(const boost::property_tree::ptree& tree) {
    this->construct(tree);
}

void Hashtag::construct(const boost::property_tree::ptree& tree) {
    text = tree.get<std::string>("text");
    auto indices_tree = tree.get_child("indices");
    int count{0};
    for (auto& pair : indices_tree) {
        indices[count++] = pair.second.get_value<int>();
    }
}

}  // namespace tal
