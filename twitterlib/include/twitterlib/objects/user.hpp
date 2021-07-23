#ifndef TWITTERLIB_OBJECTS_USER_HPP
#define TWITTERLIB_OBJECTS_USER_HPP
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/entities.hpp>

namespace twitter {

struct User {
    std::int64_t id;
    std::string name;
    std::string screen_name;
    std::optional<std::string> location;
    std::optional<std::string> url;
    std::optional<std::string> description;
    bool tweets_protected;  // "protected"
    bool verified;
    int followers_count;
    int friends_count;
    int listed_count;
    int favourites_count;
    int statuses_count;
    std::string created_at;
    std::string profile_banner_url;
    std::string profile_image_url_https;
    bool default_profile;
    bool default_profile_image;
    std::vector<std::string> withheld_in_countries;
    std::string withheld_scope;
};

/// Generates a string display of all data in \p user.
[[nodiscard]] auto to_string(User const& user) -> std::string;

/// Create a User from a property tree.
[[nodiscard]] auto parse_user(boost::property_tree::ptree const& tree) -> User;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_USER_HPP
