#ifndef TWITTERLIB_OBJECTS_PLACE_HPP
#define TWITTERLIB_OBJECTS_PLACE_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/bounding_box.hpp>
#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/place_attributes.hpp>

namespace twitter {

struct Place_data {
    explicit operator std::string() const;

    Place_attributes attributes;
    Bounding_box bounding_box;
    std::string country;
    std::string country_code;
    std::string full_name;
    std::string id;
    std::string name;
    std::string place_type;
    std::string url;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Place = Objects_template<Place_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_PLACE_HPP
