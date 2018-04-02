#ifndef NETWORKLIB_VIEW_PTREE_HPP
#define NETWORKLIB_VIEW_PTREE_HPP
#include <iostream>

#include <boost/property_tree/ptree_fwd.hpp>

namespace network {

void view_ptree(const boost::property_tree::ptree& tree,
                std::ostream& os = std::cout);

}  // namespace network
#endif  // NETWORKLIB_VIEW_PTREE_HPP
