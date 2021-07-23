#include <twitterlib/objects/entities.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/hashtag.hpp>
#include <twitterlib/objects/media.hpp>
#include <twitterlib/objects/symbol.hpp>
#include <twitterlib/objects/url.hpp>
#include <twitterlib/objects/user_mention.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Entities const& entities) -> std::string
{
    auto x = std::string{};
    x.append("hashtags:\n");
    for (auto const& hashtag : entities.hashtags)
        x.append(to_string(hashtag)).append(1, '\n');

    // TODO
    x.append("media:\n");
    for (auto const& m : entities.media)
        x.append(to_string(m)).append(1, '\n');

    x.append("urls:\n");
    for (auto const& url : entities.urls)
        x.append(to_string(url)).append(1, '\n');

    x.append("user_mentions:\n");
    for (auto const& mention : entities.user_mentions)
        x.append(to_string(mention)).append(1, '\n');

    x.append("symbols:\n");
    for (auto const& symbol : entities.symbols)
        x.append(to_string(symbol)).append(1, '\n');

    return x;
}

auto parse_entities(boost::property_tree::ptree const& tree) -> Entities
{
    auto x     = Entities{};
    x.hashtags = as_vector<Hashtag>(
        tree.get_child("hashtags", {}),
        [](auto const& tree) { return parse_hashtag(tree); });

    x.media =
        as_vector<Media>(tree.get_child("media", {}),
                         [](auto const& tree) { return parse_media(tree); });

    x.urls = as_vector<URL>(tree.get_child("urls", {}),
                            [](auto const& tree) { return parse_url(tree); });

    x.user_mentions = as_vector<User_mention>(
        tree.get_child("user_mentions", {}),
        [](auto const& tree) { return parse_user_mention(tree); });

    x.symbols =
        as_vector<Symbol>(tree.get_child("symbols", {}),
                          [](auto const& tree) { return parse_symbol(tree); });

    return x;
}

// Entities_data::operator std::string() const
// {
//     std::stringstream ss;
//     ss << "hashtags:";
//     for (const auto& ht : hashtags) {
//         ss << "\n" << ht;
//     }
//     ss << "\nmedia: ";
//     for (const auto& m : media) {
//         ss << "\n" << m;
//     }
//     ss << "\nurls: ";
//     for (const auto& url : urls) {
//         ss << "\n" << url;
//     }
//     ss << "\nuser_mentions: ";
//     for (const auto& um : user_mentions) {
//         ss << "\n" << um;
//     }
//     return ss.str();
// }

// void Entities_data::construct(const boost::property_tree::ptree& tree)
// {
//     auto hashtags_tree =
//         tree.get_child("hashtags", boost::property_tree::ptree());
//     for (auto& pair : hashtags_tree) {
//         hashtags.push_back(Hashtag{pair.second});
//     }
//     auto media_tree = tree.get_child("media", boost::property_tree::ptree());
//     for (auto& pair : media_tree) {
//         media.push_back(Media{pair.second});
//     }
//     auto urls_tree = tree.get_child("urls", boost::property_tree::ptree());
//     for (auto& pair : urls_tree) {
//         urls.push_back(URL{pair.second});
//     }
//     auto user_mentions_tree =
//         tree.get_child("user_mentions", boost::property_tree::ptree());
//     for (auto& pair : user_mentions_tree) {
//         user_mentions.push_back(User_mention{pair.second});
//     }
// }

}  // namespace twitter
