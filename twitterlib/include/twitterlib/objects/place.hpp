#ifndef TWITTERLIB_OBJECTS_PLACE_HPP
#define TWITTERLIB_OBJECTS_PLACE_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/bounding_box.hpp>

namespace twitter {

struct Place {
    std::string id;
    std::string url;
    std::string place_type;
    std::string name;
    std::string full_name;
    std::string country_code;
    std::string country;
    Bounding_box bounding_box;
};

/// Generates a string display of all data in \p place.
[[nodiscard]] auto to_string(Place const& place) -> std::string;

/// Create a Place from a property tree.
[[nodiscard]] auto parse_place(boost::property_tree::ptree const& tree)
    -> Place;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_PLACE_HPP
