#include "objects/sizes.hpp"

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include "objects/size.hpp"

namespace tal {
Sizes_data::operator std::string() const {
    std::stringstream ss;
    ss << "thumb:\n" << thumb;
    ss << "\nlarge:\n" << large;
    ss << "\nmedium:\n" << medium;
    ss << "\nsmall:\n" << small;
    return ss.str();
}

void Sizes_data::construct(const boost::property_tree::ptree& tree) {
    thumb = Size{tree.get_child("thumb", boost::property_tree::ptree())};
    large = Size{tree.get_child("large", boost::property_tree::ptree())};
    medium = Size{tree.get_child("medium", boost::property_tree::ptree())};
    small = Size{tree.get_child("small", boost::property_tree::ptree())};
}

} // namespace tal
