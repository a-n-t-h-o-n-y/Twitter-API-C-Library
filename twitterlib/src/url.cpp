#include <twitterlib/objects/url.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/indices.hpp>
#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(URL const& url) -> std::string
{
    auto x = std::string{};
    x.append("display_url: ").append(url.display_url);
    x.append("\nexpanded_url: ").append(url.expanded_url);
    x.append("\nindices: ").append(to_string(url.indices));
    x.append("\nurl: ").append(url.url);
    return x;
}

auto parse_url(boost::property_tree::ptree const& tree) -> URL
{
    auto x         = URL{};
    x.display_url  = tree.get<std::string>("display_url", {});
    x.expanded_url = tree.get<std::string>("expanded_url", {});
    x.indices      = parse_indices(tree.get_child("indices", {}));
    x.url          = tree.get<std::string>("url", {});
    return x;
}

}  // namespace twitter
