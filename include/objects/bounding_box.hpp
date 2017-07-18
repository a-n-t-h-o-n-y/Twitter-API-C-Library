#ifndef OBJECTS_BOUNDING_BOX_HPP
#define OBJECTS_BOUNDING_BOX_HPP

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>
#include "objects_template.hpp"

namespace tal {

struct Bounding_box_data {
    explicit operator std::string() const;

    std::string type;
    std::vector<std::array<float, 2>> coordinates;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Bounding_box = detail::Objects_template<Bounding_box_data>;

}  // namespace tal
#endif  // OBJECTS_BOUNDING_BOX_HPP
