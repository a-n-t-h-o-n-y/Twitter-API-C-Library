#ifndef TWITTERLIB_OBJECTS_MEDIA_HPP
#define TWITTERLIB_OBJECTS_MEDIA_HPP
#include <cstdint>
#include <optional>
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/indices.hpp>
#include <twitterlib/objects/sizes.hpp>

namespace twitter {

struct Media {
    std::string display_url;
    std::string expanded_url;
    std::int64_t id;
    Indices indices;
    std::string media_url;
    std::string media_url_https;
    Sizes sizes;
    std::optional<std::int64_t> source_status_id;
    std::string type;
    std::string url;
};

/// Generates a string display of all data in \p media.
[[nodiscard]] auto to_string(Media const& media) -> std::string;

/// Create a Media object from a property tree.
[[nodiscard]] auto parse_media(boost::property_tree::ptree const& tree)
    -> Media;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_MEDIA_HPP
