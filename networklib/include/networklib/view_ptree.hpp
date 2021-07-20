#ifndef NETWORKLIB_VIEW_PTREE_HPP
#define NETWORKLIB_VIEW_PTREE_HPP
#include <ostream>

#include <boost/property_tree/ptree_fwd.hpp>

namespace network {

void view_ptree(boost::property_tree::ptree const& tree, std::ostream& os);

}  // namespace network
#endif  // NETWORKLIB_VIEW_PTREE_HPP
