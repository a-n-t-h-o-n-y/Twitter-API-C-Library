#include <twitterlib/objects/bounding_box.hpp>

#include <array>
#include <sstream>
#include <string>

namespace twitter {

Bounding_box_data::operator std::string() const
{
    auto ss = std::ostringstream{};
    for (auto const& coords : coordinates)
        ss << "coordinates: " << coords[0] << ", " << coords[1] << '\n';

    ss << "type: " << type;
    return ss.str();
}

void Bounding_box_data::construct(boost::property_tree::ptree const& tree)
{
    type = tree.get<std::string>("type", "");
    auto const outer_tree =
        tree.get_child("coordinates", boost::property_tree::ptree());

    if (outer_tree.empty())
        return;

    auto const bounding_tree = outer_tree.front().second;
    for (auto const& tree : bounding_tree) {
        coordinates.push_back({0., 0.});
        auto count = 0;
        for (const auto& coord : tree.second)
            coordinates.back()[count++] = coord.second.get_value<float>(-1.0);
    }
}

}  // namespace twitter
