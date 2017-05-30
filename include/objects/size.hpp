#ifndef SIZE_HPP
#define SIZE_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "objects_template.hpp"

namespace tal {

struct Size_data {
    explicit operator std::string() const;

    int height;
    int width;
    std::string resize;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Size = detail::Objects_template<Size_data>;

}  // namespace tal
#endif  // SIZE_HPP
