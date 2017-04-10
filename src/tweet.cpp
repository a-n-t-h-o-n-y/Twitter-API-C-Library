#include "objects/tweet.hpp"

#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>

namespace tal {

Tweet_data::operator std::string() const {
    std::stringstream ss;

    return ss.str();
}

void Tweet_data::construct(const boost::property_tree::ptree& tree) {

}
}  // namespace tal
