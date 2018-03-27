#ifndef DETAIL_URL_HPP
#define DETAIL_URL_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>

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
#endif  // DETAIL_URL_HPP
