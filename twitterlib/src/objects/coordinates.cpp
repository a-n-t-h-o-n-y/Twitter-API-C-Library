#include <twitterlib/objects/coordinates.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/detail/utility.hpp>

namespace twitter {

auto to_string(Earth_coordinates const& ec) -> std::string
{
    auto x = std::string{};
    x.append("[long: ")
        .append(to_string(ec.longitude))
        .append(", lat: ")
        .append(to_string(ec.latitude))
        .append(1, ']');
    return x;
}

auto parse_earth_coordinates(boost::property_tree::ptree const& tree)
    -> Earth_coordinates
{
    auto x         = Earth_coordinates{};
    auto const vec = as_vector<float>(tree);
    if (vec.size() == 2) {
        x.longitude = vec[0];
        x.latitude  = vec[1];
    }
    return x;
}

auto to_string(Coordinates const& coordinates) -> std::string
{
    auto x = std::string{};
    x.append("coordinates: ").append(to_string(coordinates.coordinates));
    x.append("\ntype: ").append(coordinates.type);
    return x;
}

auto parse_coordinates(boost::property_tree::ptree const& tree) -> Coordinates
{
    auto x        = Coordinates{};
    x.coordinates = parse_earth_coordinates(tree.get_child("coordinates", {}));
    x.type        = tree.get<std::string>("type", {});
    return x;
}

}  // namespace twitter
