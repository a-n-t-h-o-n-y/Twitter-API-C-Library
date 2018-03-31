#ifndef TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
#define TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

struct Bounding_box_data {
    explicit operator std::string() const;

    std::string type;
    std::vector<std::array<float, 2>> coordinates;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Bounding_box = Objects_template<Bounding_box_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
