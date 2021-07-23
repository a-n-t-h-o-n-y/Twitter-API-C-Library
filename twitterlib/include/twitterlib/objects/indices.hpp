#ifndef TWITTERLIB_OBJECTS_INDICES_HPP
#define TWITTERLIB_OBJECTS_INDICES_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

namespace twitter {

using Indices = std::array<int, 2>;

/// Generates a string display of all data in \p indices.
[[nodiscard]] auto to_string(Indices const& indices) -> std::string;

/// Create an Indices object from a property tree.
[[nodiscard]] auto parse_indices(boost::property_tree::ptree const& tree)
    -> Indices;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_INDICES_HPP
