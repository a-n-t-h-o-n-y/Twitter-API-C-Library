#ifndef TWITTERLIB_OBJECTS_SIZE_HPP
#define TWITTERLIB_OBJECTS_SIZE_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

namespace twitter {

struct Size {
    int w;
    int h;
    std::string resize;
};

/// Generates a string display of all data in \p size.
[[nodiscard]] auto to_string(Size const& size) -> std::string;

/// Create a Size object from a property tree.
[[nodiscard]] auto parse_size(boost::property_tree::ptree const& tree) -> Size;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_SIZE_HPP
