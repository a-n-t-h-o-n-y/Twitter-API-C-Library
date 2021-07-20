#ifndef NETWORKLIB_RESPONSE_HPP
#define NETWORKLIB_RESPONSE_HPP
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace network {

using Response = std::string;

/// Convert a Response into a boost ptree, assumes the Response is JSON.
[[nodiscard]] auto to_ptree(Response const& json)
    -> boost::property_tree::ptree;

/// Returns the value associated with \p key from \p tree.
[[nodiscard]] auto get(boost::property_tree::ptree const& tree,
                       std::string const& key) -> std::string;

}  // namespace network
#endif  // NETWORKLIB_RESPONSE_HPP
