#include <twitterlib/objects/place.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Place const& place) -> std::string
{
    auto x = std::string{};
    x.append("id: ").append(place.id);
    x.append("\nurl: ").append(place.url);
    x.append("\nplace_type: ").append(place.place_type);
    x.append("\nname: ").append(place.name);
    x.append("\nfull_name: ").append(place.full_name);
    x.append("\ncountry_code: ").append(place.country_code);
    x.append("\ncountry: ").append(place.country);
    x.append("\nbounding_box:\n")
        .append(add_indention_level(to_string(place.bounding_box)));
    return x;
}

auto parse_place(boost::property_tree::ptree const& tree) -> Place
{
    auto x         = Place{};
    x.id           = tree.get<std::string>("id", {});
    x.url          = tree.get<std::string>("url", {});
    x.place_type   = tree.get<std::string>("place_type", {});
    x.name         = tree.get<std::string>("name", {});
    x.full_name    = tree.get<std::string>("full_name", {});
    x.country_code = tree.get<std::string>("country_code", {});
    x.country      = tree.get<std::string>("country", {});
    x.bounding_box = parse_bounding_box(tree.get_child("bounding_box", {}));
    return x;
}

}  // namespace twitter
