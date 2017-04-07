#include "objects/size.hpp"

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace tal {

Size::Size(const std::string& json) {
    boost::property_tree::ptree tree;
    std::istringstream ss(json);
    boost::property_tree::read_json(ss, tree);
    this->construct(tree);
}

Size::Size(const boost::property_tree::ptree& tree) {
    this->construct(tree);
}

Size::operator std::string() const {
    std::stringstream ss;
    ss << "height: " << height;
    ss << "\nwidth: " << width;
    ss << "\nresize: " << resize;
    return ss.str();
}

void Size::construct(const boost::property_tree::ptree& tree) {
    height = tree.get<int>("h");
    width = tree.get<int>("w");
    resize = tree.get<std::string>("resize");
}

}  // namespace tal
