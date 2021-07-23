#include <twitterlib/objects/bounding_box.hpp>

#include <string>

#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Bounding_box const& bounding_box) -> std::string
{
    auto x = std::string{};
    x.append("coordinates:\n");
    for (auto const& coordinate : bounding_box.coordinates)
        x.append(to_string(coordinate)).append(1, '\n');
    x.append("type: ").append(bounding_box.type);
    return x;
}

auto parse_bounding_box(boost::property_tree::ptree const& tree) -> Bounding_box
{
    auto x = Bounding_box{};

    auto const bb = tree.get_child_optional("coordinates");
    if (!bb.has_value())
        return x;

    auto const bounding_tree = bb->front().second;
    for (auto const& tree : bounding_tree)
        x.coordinates.push_back(parse_earth_coordinates(tree.second));
    x.type = tree.get<std::string>("type", {});
    return x;
}

}  // namespace twitter
