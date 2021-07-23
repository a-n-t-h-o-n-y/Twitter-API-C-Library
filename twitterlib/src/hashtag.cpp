#include <twitterlib/objects/hashtag.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/indices.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Hashtag const& hashtag) -> std::string
{
    auto x = std::string{};
    x.append("indices: ").append(to_string(hashtag.indices));
    x.append("\ntext: ").append(hashtag.text);
    return x;
}

auto parse_hashtag(boost::property_tree::ptree const& tree) -> Hashtag
{
    auto x    = Hashtag{};
    x.indices = parse_indices(tree.get_child("indices", {}));
    x.text    = tree.get<std::string>("text", {});
    return x;
}

}  // namespace twitter
