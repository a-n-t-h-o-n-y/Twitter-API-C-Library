#ifndef SIZES_HPP
#define SIZES_HPP

#include <string>
#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include "size.hpp"
#include "objects_template.hpp"

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
#endif  // SIZES_HPP
