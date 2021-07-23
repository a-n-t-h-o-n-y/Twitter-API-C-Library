#ifndef TWITTERLIB_OBJECTS_USER_MENTION_HPP
#define TWITTERLIB_OBJECTS_USER_MENTION_HPP
#include <cstdint>
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/indices.hpp>

namespace twitter {

struct User_mention {
    std::int64_t id;
    Indices indices;
    std::string name;
    std::string screen_name;
};

/// Generates a string display of all data in \p user_mention.
[[nodiscard]] auto to_string(User_mention const& user_mention) -> std::string;

/// Create a User_mention object from a property tree.
[[nodiscard]] auto parse_user_mention(boost::property_tree::ptree const& tree)
    -> User_mention;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_USER_MENTION_HPP
