#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <array>
#include <string>
#include <boost/property_tree/ptree_fwd.hpp>
#include "objects_template.hpp"

namespace tal {

struct Coordinates_data {
    explicit operator std::string() const;

    float longitude;
    float latitude;
    std::string type;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Coordinates = detail::Objects_template<Coordinates_data>;

}  // namespace tal
#endif  // COORDINATES_HPP
