#include <twitterlib/objects/tweet.hpp>

#include <cstdint>
#include <memory>
#include <string>

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/coordinates.hpp>
#include <twitterlib/objects/entities.hpp>
#include <twitterlib/objects/place.hpp>
#include <twitterlib/objects/user.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Tweet const& tweet) -> std::string
{
    auto x = std::string{};
    x.append("created_at: ").append(tweet.created_at);
    x.append("\nid: ").append(to_string(tweet.id));
    x.append("\ntext: ").append(tweet.text);
    x.append("\nsource: ").append(tweet.source);
    x.append("\ntruncated: ").append(to_string(tweet.truncated));
    if (tweet.in_reply_to_status_id.has_value()) {
        x.append("\nin_reply_to_status_id: ");
        x.append(to_string(tweet.in_reply_to_status_id.value()));
    }
    if (tweet.in_reply_to_user_id.has_value()) {
        x.append("\nin_reply_to_user_id: ");
        x.append(to_string(tweet.in_reply_to_user_id.value()));
    }
    if (tweet.in_reply_to_screen_name.has_value()) {
        x.append("\nin_reply_to_screen_name: ");
        x.append(tweet.in_reply_to_screen_name.value());
    }
    x.append(line);
    x.append("\nuser:\n").append(to_string(tweet.user));
    x.append(line);
    if (tweet.coordinates.has_value()) {
        x.append("\ncoordinates:\n");
        x.append(to_string(tweet.coordinates.value()));
    }
    if (tweet.place.has_value()) {
        x.append("\nplace:\n");
        x.append(to_string(tweet.place.value()));
    }
    if (tweet.quoted_status_id.has_value()) {
        x.append("\nquoted_status_id: ");
        x.append(to_string(tweet.quoted_status_id.value()));
    }
    x.append("\nis_quote_status: ").append(to_string(tweet.is_quote_status));
    if (tweet.quoted_status != nullptr) {
        x.append(line);
        x.append("\nquoted_status: ");
        x.append(to_string(*tweet.quoted_status));
        x.append(line);
    }
    if (tweet.retweeted_status != nullptr) {
        x.append(line);
        x.append("\nretweeted_status: ");
        x.append(to_string(*tweet.retweeted_status));
        x.append(line);
    }
    x.append("\nretweet_count: ").append(to_string(tweet.retweet_count));
    x.append("\nfavorite_count: ").append(to_string(tweet.favorite_count));

    x.append("\nentities:\n").append(to_string(tweet.entities));

    if (tweet.favorited.has_value())
        x.append("\nfavorited: ").append(to_string(tweet.favorited.value()));
    if (tweet.retweeted.has_value())
        x.append("\nretweeted: ").append(to_string(tweet.retweeted.value()));
    if (tweet.possibly_sensitive.has_value()) {
        x.append("\npossibly_sensitive: ");
        x.append(to_string(tweet.possibly_sensitive.value()));
    }
    x.append("\nfilter_level: ").append(tweet.filter_level);
    if (tweet.lang.has_value())
        x.append("\nlang: ").append(tweet.lang.value());
    if (tweet.current_user_retweet_id.has_value()) {
        x.append("\ncurrent_user_retweet_id: ");
        x.append(to_string(tweet.current_user_retweet_id.value()));
    }
    x.append("\nwithheld_copyright: ")
        .append(to_string(tweet.withheld_copyright));

    x.append("\nwithheld_in_countries: [\n");
    for (auto const& country : tweet.withheld_in_countries)
        x.append(country).append(",\n");
    x.append("]");

    x.append("\nwithheld_scope: ").append(tweet.withheld_scope);

    return x;
}

auto parse_tweet(boost::property_tree::ptree const& tree) -> Tweet
{
    auto x = Tweet{};

    x.created_at = tree.get<std::string>("created_at", {});
    x.id         = tree.get<std::int64_t>("id", -1);
    x.text       = tree.get<std::string>("text", {});
    x.source     = tree.get<std::string>("source", {});
    x.truncated  = tree.get<bool>("truncated", false);
    x.in_reply_to_status_id =
        to_std(tree.get_optional<std::int64_t>("in_reply_to_status_id"));
    x.in_reply_to_user_id =
        to_std(tree.get_optional<std::int64_t>("in_reply_to_user_id"));
    x.in_reply_to_screen_name =
        to_std(tree.get_optional<std::string>("in_reply_to_screen_name"));
    x.user = parse_user(tree.get_child("user", {}));

    {
        auto const coords = tree.get_child_optional("coordinates");
        if (coords.has_value())
            x.coordinates = parse_coordinates(coords.value());
    }
    {
        auto const place = tree.get_child_optional("place");
        if (place.has_value())
            x.place = parse_place(place.value());
    }
    x.quoted_status_id =
        to_std(tree.get_optional<std::int64_t>("quoted_status_id"));
    x.is_quote_status = tree.get<bool>("is_quote_status", false);

    {
        auto t = tree.get_child_optional("quoted_status");
        if (t.has_value())
            x.quoted_status = std::make_unique<Tweet>(parse_tweet(t.value()));
    }
    {
        auto t = tree.get_child_optional("retweeted_status");
        if (t.has_value())
            x.quoted_status = std::make_unique<Tweet>(parse_tweet(t.value()));
    }
    x.retweet_count  = tree.get<int>("retweet_count", -1);
    x.favorite_count = tree.get<int>("favorite_count", -1);
    x.entities       = parse_entities(tree.get_child("entities", {}));
    x.favorited      = to_std(tree.get_optional<bool>("favorited"));
    x.retweeted      = to_std(tree.get_optional<bool>("retweeted"));
    x.possibly_sensitive =
        to_std(tree.get_optional<bool>("possibly_sensitive"));
    x.filter_level = tree.get<std::string>("filter_level", {});
    x.lang         = to_std(tree.get_optional<std::string>("lang"));
    x.current_user_retweet_id =
        to_std(tree.get_optional<std::int64_t>("current_user_retweet_id"));
    x.withheld_copyright = tree.get<bool>("withheld_copyright", false);
    {
        auto const countries = tree.get_child_optional("withheld_in_countries");
        if (countries.has_value())
            x.withheld_in_countries = as_vector<std::string>(countries.value());
    }
    x.withheld_scope = tree.get<std::string>("withheld_scope", {});

    return x;
}

}  // namespace twitter
