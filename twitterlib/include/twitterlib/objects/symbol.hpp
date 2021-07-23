#ifndef TWITTERLIB_OBJECTS_SYMBOL_HPP
#define TWITTERLIB_OBJECTS_SYMBOL_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/indices.hpp>

namespace twitter {

struct Symbol {
    Indices indices;
    std::string text;
};

/// Generates a string display of all data in \p symbol.
[[nodiscard]] auto to_string(Symbol const& symbol) -> std::string;

/// Create a Symbol from a property tree.
[[nodiscard]] auto parse_symbol(boost::property_tree::ptree const& tree)
    -> Symbol;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_SYMBOL_HPP
