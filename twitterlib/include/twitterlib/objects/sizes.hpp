#ifndef TWITTERLIB_OBJECTS_SIZES_HPP
#define TWITTERLIB_OBJECTS_SIZES_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/size.hpp>

namespace twitter {

struct Sizes {
    Size thumb;
    Size large;
    Size medium;
    Size small;
};

/// Generates a string display of all data in \p sizes.
[[nodiscard]] auto to_string(Sizes const& sizes) -> std::string;

/// Create a Sizes object from a property tree.
[[nodiscard]] auto parse_sizes(boost::property_tree::ptree const& tree)
    -> Sizes;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_SIZES_HPP
