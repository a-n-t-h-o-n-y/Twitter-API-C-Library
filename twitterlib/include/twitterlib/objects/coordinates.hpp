#ifndef TWITTERLIB_OBJECTS_COORDINATES_HPP
#define TWITTERLIB_OBJECTS_COORDINATES_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

namespace twitter {

struct Earth_coordinates {
    float longitude = 0.f;
    float latitude  = 0.f;
};

/// Generates a string display of all data in \p ec.
[[nodiscard]] auto to_string(Earth_coordinates const& ec) -> std::string;

/// Create an Earth_coordinates struct from a property tree.
[[nodiscard]] auto parse_earth_coordinates(
    boost::property_tree::ptree const& tree) -> Earth_coordinates;

struct Coordinates {
    Earth_coordinates coordinates;
    std::string type;
};

/// Generates a string display of all data in \p coordinates.
[[nodiscard]] auto to_string(Coordinates const& coordinates) -> std::string;

/// Create a Coordinates struct from a property tree.
[[nodiscard]] auto parse_coordinates(boost::property_tree::ptree const& tree)
    -> Coordinates;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_COORDINATES_HPP
