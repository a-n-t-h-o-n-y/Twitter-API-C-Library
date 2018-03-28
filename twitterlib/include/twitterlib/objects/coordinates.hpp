#ifndef TWITTERLIB_OBJECTS_COORDINATES_HPP
#define TWITTERLIB_OBJECTS_COORDINATES_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

struct Coordinates_data {
    explicit operator std::string() const;

    float longitude = 0.0;
    float latitude = 0.0;
    std::string type;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Coordinates = Objects_template<Coordinates_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_COORDINATES_HPP
