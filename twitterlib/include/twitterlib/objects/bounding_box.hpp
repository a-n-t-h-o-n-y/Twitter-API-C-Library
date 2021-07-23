#ifndef TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
#define TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
#include <string>
#include <vector>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/coordinates.hpp>

namespace twitter {

struct Bounding_box {
    std::vector<Earth_coordinates> coordinates;
    std::string type;
};

/// Generates a string display of all data in \p bounding_box.
[[nodiscard]] auto to_string(Bounding_box const& bounding_box) -> std::string;

/// Create a Bounding_box from a property tree.
[[nodiscard]] auto parse_bounding_box(boost::property_tree::ptree const& tree)
    -> Bounding_box;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
