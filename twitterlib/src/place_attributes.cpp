#include <twitterlib/objects/place_attributes.hpp>

#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace twitter {

Place_attributes_data::operator std::string() const {
    std::stringstream ss;
    ss << "street_address: " << street_address << "\nlocality: " << locality
       << "\nregion: " << region << "\niso3: " << iso3
       << "\npostal_code: " << postal_code << "\nphone: " << phone
       << "\ntwitter: " << twitter << "\nurl: " << url
       << "\napp:id: " << app_id;
    return ss.str();
}

void Place_attributes_data::construct(const boost::property_tree::ptree& tree) {
    street_address = tree.get<std::string>("street_address", "");
    locality = tree.get<std::string>("locality", "");
    region = tree.get<std::string>("region", "");
    iso3 = tree.get<std::string>("iso3", "");
    postal_code = tree.get<std::string>("postal_code", "");
    phone = tree.get<std::string>("phone", "");
    twitter = tree.get<std::string>("twitter", "");
    url = tree.get<std::string>("url", "");
    app_id = tree.get<std::string>("app:id", "");
}

}  // namespace twitter
