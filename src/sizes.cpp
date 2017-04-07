#include "objects/sizes.hpp"

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "objects/size.hpp"

namespace tal {

Sizes::Sizes(const std::string& json) {
    boost::property_tree::ptree tree;
    std::istringstream ss(json);
    boost::property_tree::read_json(ss, tree);
    this->construct(tree);
}

Sizes::Sizes(const boost::property_tree::ptree& tree) {
    this->construct(tree);
}

Sizes::operator std::string() const {
    std::stringstream ss;
    ss << "thumb: " << thumb;
    ss << "\nlarge: " << large;
    ss << "\nmedium: " << medium;
    ss << "\nsmall: " << small;
    return ss.str();
}

void Sizes::construct(const boost::property_tree::ptree& tree) {
    thumb = Size{tree.get_child("thumb")};
    large = Size{tree.get_child("large")};
    medium = Size{tree.get_child("medium")};
    small = Size{tree.get_child("small")};
}

} // namespace tal
