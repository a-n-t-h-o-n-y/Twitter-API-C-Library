#ifndef TWITTERLIB_OBJECTS_ENTITIES_HPP
#define TWITTERLIB_OBJECTS_ENTITIES_HPP
#include <string>
#include <vector>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/hashtag.hpp>
#include <twitterlib/objects/media.hpp>
#include <twitterlib/objects/symbol.hpp>
#include <twitterlib/objects/url.hpp>
#include <twitterlib/objects/user_mention.hpp>

namespace twitter {

struct Entities {
    std::vector<Hashtag> hashtags;
    std::vector<Media> media;
    std::vector<URL> urls;
    std::vector<User_mention> user_mentions;
    std::vector<Symbol> symbols;
};

/// Generates a string display of all data in \p entities.
[[nodiscard]] auto to_string(Entities const& entities) -> std::string;

/// Create an Entities object from a property tree.
[[nodiscard]] auto parse_entities(boost::property_tree::ptree const& tree)
    -> Entities;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_ENTITIES_HPP
