#ifndef DETAIL_SIZES_HPP
#define DETAIL_SIZES_HPP
#include <ostream>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/size.hpp>

namespace tal {

struct Sizes_data {
    explicit operator std::string() const;

    Size thumb;
    Size large;
    Size medium;
    Size small;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Sizes = detail::Objects_template<Sizes_data>;

}  // namespace tal
#endif  // DETAIL_SIZES_HPP
