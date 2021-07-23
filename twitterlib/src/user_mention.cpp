#include <twitterlib/objects/user_mention.hpp>

#include <cstdint>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/indices.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(User_mention const& user_mention) -> std::string
{
    auto x = std::string{};
    x.append("id: ").append(to_string(user_mention.id));
    x.append("\nindicies: ").append(to_string(user_mention.indices));
    x.append("\nname: ").append(user_mention.name);
    x.append("\nscreen_name: ").append(user_mention.screen_name);
    return x;
}

auto parse_user_mention(boost::property_tree::ptree const& tree) -> User_mention
{
    auto x        = User_mention{};
    x.id          = tree.get<std::int64_t>("id", -1);
    x.indices     = parse_indices(tree.get_child("indices", {}));
    x.name        = tree.get<std::string>("name", {});
    x.screen_name = tree.get<std::string>("screen_name", {});
    return x;
}

}  // namespace twitter
