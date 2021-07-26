#include <twitterlib/objects/size.hpp>

#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/detail/utility.hpp>

namespace twitter {

auto to_string(Size const& size) -> std::string
{
    auto x = std::string{};
    x.append("w: ").append(to_string(size.w));
    x.append("\nh: ").append(to_string(size.h));
    x.append("\nresize: ").append(size.resize);
    return x;
}

auto parse_size(boost::property_tree::ptree const& tree) -> Size
{
    auto x   = Size{};
    x.w      = tree.get<int>("w", -1);
    x.h      = tree.get<int>("h", -1);
    x.resize = tree.get<std::string>("resize", {});
    return x;
}

}  // namespace twitter
