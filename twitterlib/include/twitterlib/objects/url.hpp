#ifndef TWITTERLIB_OBJECTS_URL_HPP
#define TWITTERLIB_OBJECTS_URL_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/indices.hpp>

namespace twitter {

struct URL {
    std::string display_url;
    std::string expanded_url;
    Indices indices;
    std::string url;
};

/// Generates a string display of all data in \p url.
[[nodiscard]] auto to_string(URL const& url) -> std::string;

/// Create a URL object from a property tree.
[[nodiscard]] auto parse_url(boost::property_tree::ptree const& tree) -> URL;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_URL_HPP
