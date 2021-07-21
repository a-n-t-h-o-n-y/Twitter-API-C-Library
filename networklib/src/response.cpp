#include <networklib/response.hpp>

#include <sstream>
#include <string>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace network {

auto to_ptree(Response const& json) -> boost::property_tree::ptree
{
    auto tree = boost::property_tree::ptree{};
    auto ss   = std::istringstream{json};
    boost::property_tree::read_json(ss, tree);
    return tree;
}

auto get(boost::property_tree::ptree const& tree, std::string const& key)
    -> std::string
{
    return tree.get<std::string>(key, "");
}

}  // namespace network
