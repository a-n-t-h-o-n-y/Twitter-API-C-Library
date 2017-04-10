#ifndef PLACE_HPP
#define PLACE_HPP

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>
#include "objects_template.hpp"
#include "place_attributes.hpp"
#include "bounding_box.hpp"

namespace tal {

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

using Place = detail::Objects_template<Place_data>;

}  // namespace tal
#endif  // PLACE_HPP
