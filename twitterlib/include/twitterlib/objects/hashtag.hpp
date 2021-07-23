#ifndef TWITTERLIB_OBJECTS_HASHTAG_HPP
#define TWITTERLIB_OBJECTS_HASHTAG_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/indices.hpp>

namespace twitter {

struct Hashtag {
    Indices indices;
    std::string text;
};

/// Generates a string display of all data in \p hashtag.
[[nodiscard]] auto to_string(Hashtag const& hashtag) -> std::string;

/// Create a Hashtag object from a property tree.
[[nodiscard]] auto parse_hashtag(boost::property_tree::ptree const& tree)
    -> Hashtag;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_HASHTAG_HPP
