#include <twitterlib/objects/size.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace twitter {

Size_data::operator std::string() const {
    std::stringstream ss;
    ss << "height: " << height;
    ss << "\nwidth: " << width;
    ss << "\nresize: " << resize;
    return ss.str();
}

void Size_data::construct(const boost::property_tree::ptree& tree) {
    height = tree.get<int>("h", -1);
    width = tree.get<int>("w", -1);
    resize = tree.get<std::string>("resize", "");
}

}  // namespace twitter
