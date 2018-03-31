#ifndef TWITTERLIB_OBJECTS_PLACE_ATTRIBUTES_HPP
#define TWITTERLIB_OBJECTS_PLACE_ATTRIBUTES_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

struct Place_attributes_data {
    explicit operator std::string() const;

    std::string street_address;
    std::string locality;
    std::string region;
    std::string iso3;
    std::string postal_code;
    std::string phone;
    std::string twitter;
    std::string url;
    std::string app_id;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Place_attributes = Objects_template<Place_attributes_data>;

};      // namespace twitter
#endif  // TWITTERLIB_OBJECTS_PLACE_ATTRIBUTES_HPP
