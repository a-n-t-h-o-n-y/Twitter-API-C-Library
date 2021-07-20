#ifndef TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
#define TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

class Bounding_box_data {
   public:
    std::string type;
    std::vector<std::array<float, 2>> coordinates;

   public:
    [[nodiscard]] explicit operator std::string() const;

   protected:
    void construct(boost::property_tree::ptree const& tree);
};

using Bounding_box = Objects_template<Bounding_box_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_BOUNDING_BOX_HPP
