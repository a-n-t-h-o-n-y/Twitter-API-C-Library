#ifndef SIZES_HPP
#define SIZES_HPP

#include <string>
#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include "objects/size.hpp"

namespace tal {

struct Sizes {
    Sizes() = default;
    explicit Sizes(const std::string& json);
    explicit Sizes(const boost::property_tree::ptree& tree);

    explicit operator std::string() const;

    Size thumb;
    Size large;
    Size medium;
    Size small;

   private:
    void construct(const boost::property_tree::ptree& tree);
};

inline std::ostream& operator<<(std::ostream& os, const Sizes& sizes) {
    return os << static_cast<std::string>(sizes);
}

}  // namespace tal
#endif  // SIZES_HPP
