#include "objects/bounding_box.hpp"

#include <array>
#include <string>
#include <sstream>

namespace tal {

Bounding_box_data::operator std::string() const {
    std::stringstream ss;
    for (const auto& coords : coordinates) {
        ss << "coordinates: " << coords[0] << ", " << coords[1] << '\n';
    }
    ss << "type: " << type;
    return ss.str();
}

void Bounding_box_data::construct(const boost::property_tree::ptree& tree) {
    type = tree.get<std::string>("type", "");
    auto bounding_tree = tree.get_child("coordinates").front().second;
    for (const auto& tree : bounding_tree) {
        coordinates.push_back(std::array<float, 2>{0.0});
        int count{0};
        for (const auto& coord : tree.second) {
            coordinates.back()[count++] = coord.second.get_value<float>(0.0);
        }
    }
}

}  // namespace tal
