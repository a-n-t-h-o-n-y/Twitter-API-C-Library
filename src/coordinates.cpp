#include "objects/coordinates.hpp"

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>

namespace tal {

Coordinates_data::operator std::string() const {
    std::stringstream ss;
    ss << "longitude: " << longitude
       << "\nlatitude: " << latitude
       << "\ntype: " << type;
    return ss.str();
}

void Coordinates_data::construct(const boost::property_tree::ptree& tree) {
    auto coordinates_tree = tree.get_child("coordinates");
    longitude = coordinates_tree.front().second.get_value<float>(0.0);
    latitude = coordinates_tree.back().second.get_value<float>(0.0);
    type = tree.get<std::string>("type", "");
}
}  // namespace tal
