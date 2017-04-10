#ifndef URL_HPP
#define URL_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "objects_template.hpp"

namespace tal {

struct URL_data {
    explicit operator std::string() const;

    std::string display_url;
    std::string expanded_url;
    std::string url;
    std::array<int, 2> indices;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using URL = detail::Objects_template<URL_data>;

}  // namespace tal
#endif  // URL_HPP
