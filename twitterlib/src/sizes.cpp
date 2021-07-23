#include <twitterlib/objects/sizes.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/size.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Sizes const& sizes) -> std::string
{
    auto x = std::string{};
    x.append("thumb:\n").append(add_indention_level(to_string(sizes.thumb)));
    x.append("\nlarge:\n").append(add_indention_level(to_string(sizes.large)));
    x.append("\nmedium:\n")
        .append(add_indention_level(to_string(sizes.medium)));
    x.append("\nsmall:\n").append(add_indention_level(to_string(sizes.small)));
    return x;
}

auto parse_sizes(boost::property_tree::ptree const& tree) -> Sizes
{
    auto x   = Sizes{};
    x.thumb  = parse_size(tree.get_child("thumb", {}));
    x.large  = parse_size(tree.get_child("large", {}));
    x.medium = parse_size(tree.get_child("medium", {}));
    x.small  = parse_size(tree.get_child("small", {}));
    return x;
}

}  // namespace twitter
