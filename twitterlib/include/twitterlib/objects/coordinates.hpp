#ifndef TWITTERLIB_OBJECTS_COORDINATES_HPP
#define TWITTERLIB_OBJECTS_COORDINATES_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

class Coordinates_data {
   public:
    float longitude = 0.;
    float latitude  = 0.;
    std::string type;

   public:
    [[nodiscard]] explicit operator std::string() const;

   protected:
    void construct(boost::property_tree::ptree const& tree);
};

using Coordinates = Objects_template<Coordinates_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_COORDINATES_HPP
