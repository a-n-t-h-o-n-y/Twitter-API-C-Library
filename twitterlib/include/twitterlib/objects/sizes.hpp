#ifndef TWITTERLIB_OBJECTS_SIZES_HPP
#define TWITTERLIB_OBJECTS_SIZES_HPP
#include <ostream>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/size.hpp>

namespace twitter {

struct Sizes_data {
    explicit operator std::string() const;

    Size thumb;
    Size large;
    Size medium;
    Size small;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Sizes = Objects_template<Sizes_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_SIZES_HPP
