#include <networklib/view_ptree.hpp>

#include <ostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace network {

void view_ptree(boost::property_tree::ptree const& tree, std::ostream& os)
{
    boost::property_tree::json_parser::write_json(os, tree);
}

}  // namespace network
