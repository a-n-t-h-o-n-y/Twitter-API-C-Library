#ifndef HASHTAG_HPP
#define HASHTAG_HPP

#include <string>
#include <array>
#include <boost/property_tree/ptree.hpp>
#include "objects_template.hpp"

namespace tal {

struct Hashtag_data {
    explicit operator std::string() const;

    std::string text;
    std::array<int, 2> indices;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Hashtag = detail::Objects_template<Hashtag_data>;

}  // namespace tal
#endif  // HASHTAG_HPP
