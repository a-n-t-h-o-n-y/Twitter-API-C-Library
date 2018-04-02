#include <networklib/view_ptree.hpp>

#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace network {

void view_ptree(const boost::property_tree::ptree& tree, std::ostream& os) {
    boost::property_tree::json_parser::write_json(std::cout, tree);
}

}  // namespace network
