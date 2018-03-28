#include <twitterlib/objects/place.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace twitter {

Place_data::operator std::string() const {
    std::stringstream ss;
    ss << "attributes:\n"
       << attributes << "\nbounding_box:\n"
       << bounding_box << "\ncountry: " << country
       << "\ncoutry_code: " << country_code << "\nfull_name: " << full_name
       << "\nid: " << id << "\nname: " << name << "\nplace_type: " << place_type
       << "\nurl: " << url;
    return ss.str();
}

void Place_data::construct(const boost::property_tree::ptree& tree) {
    attributes = Place_attributes{
        tree.get_child("attributes", boost::property_tree::ptree())};
    bounding_box = Bounding_box{
        tree.get_child("bounding_box", boost::property_tree::ptree())};
    country = tree.get<std::string>("country", "");
    country_code = tree.get<std::string>("country_code", "");
    full_name = tree.get<std::string>("full_name", "");
    id = tree.get<std::string>("id", "");
    name = tree.get<std::string>("name", "");
    place_type = tree.get<std::string>("place_type", "");
    url = tree.get<std::string>("url", "");
}

}  // namespace twitter
