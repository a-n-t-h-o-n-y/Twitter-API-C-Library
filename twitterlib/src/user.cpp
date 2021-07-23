#include <twitterlib/objects/user.hpp>

#include <cstdint>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/tweet.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(User const& user) -> std::string
{
    auto x = std::string{};
    x.append("id: ").append(to_string(user.id));
    x.append("\nname: ").append(user.name);
    x.append("\nscreen_name: ").append(user.screen_name);
    if (user.location.has_value())
        x.append("\nlocation: ").append(user.location.value());
    if (user.url.has_value())
        x.append("\nurl: ").append(user.url.value());
    if (user.description.has_value())
        x.append("\ndescription: ").append(user.description.value());
    x.append("\n(tweets_)protected: ").append(to_string(user.tweets_protected));
    x.append("\nverified: ").append(to_string(user.verified));
    x.append("\nfollowers_count: ").append(to_string(user.followers_count));
    x.append("\nfriends_count: ").append(to_string(user.friends_count));
    x.append("\nlisted_count: ").append(to_string(user.listed_count));
    x.append("\nfavourites_count: ").append(to_string(user.favourites_count));
    x.append("\nstatuses_count: ").append(to_string(user.statuses_count));
    x.append("\ncreated_at: ").append(user.created_at);
    x.append("\nprofile_banner_url: ").append(user.profile_banner_url);
    x.append("\nprofile_image_url_https: ")
        .append(user.profile_image_url_https);
    x.append("\ndefault_profile: ").append(to_string(user.default_profile));
    x.append("\ndefault_profile_image: ")
        .append(to_string(user.default_profile_image));

    x.append("\nwithheld_in_countries: [");
    for (auto const& country : user.withheld_in_countries)
        x.append(1, '\n').append(add_indention_level(country)).append(1, ',');
    x.append("]");

    x.append("\nwithheld_scope: ").append(user.withheld_scope);

    return x;
}

auto parse_user(boost::property_tree::ptree const& tree) -> User
{
    auto x             = User{};
    x.id               = tree.get<std::int64_t>("id", -1);
    x.name             = tree.get<std::string>("name", {});
    x.screen_name      = tree.get<std::string>("screen_name", {});
    x.location         = to_std(tree.get_optional<std::string>("location"));
    x.url              = to_std(tree.get_optional<std::string>("url"));
    x.description      = to_std(tree.get_optional<std::string>("description"));
    x.tweets_protected = tree.get<bool>("protected", false);
    x.verified         = tree.get<bool>("verified", false);
    x.followers_count  = tree.get<int>("followers_count", -1);
    x.friends_count    = tree.get<int>("friends_count", -1);
    x.listed_count     = tree.get<int>("listed_count", -1);
    x.favourites_count = tree.get<int>("favourites_count", -1);
    x.statuses_count   = tree.get<int>("statuses_count", -1);
    x.created_at       = tree.get<std::string>("created_at", {});
    x.profile_banner_url = tree.get<std::string>("profile_banner_url", {});
    x.profile_image_url_https =
        tree.get<std::string>("profile_image_url_https", {});
    x.default_profile       = tree.get<bool>("default_profile", false);
    x.default_profile_image = tree.get<bool>("default_profile_image", false);
    {
        auto const countries = tree.get_child_optional("withheld_in_countries");
        if (countries.has_value())
            x.withheld_in_countries = as_vector<std::string>(countries.value());
    }
    x.withheld_scope = tree.get<std::string>("withheld_scope", {});
    return x;
}

}  // namespace twitter
