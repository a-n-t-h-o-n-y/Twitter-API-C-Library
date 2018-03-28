#ifndef TWITTERLIB_OBJECTS_URL_HPP
#define TWITTERLIB_OBJECTS_URL_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

struct URL_data {
    explicit operator std::string() const;

    std::string display_url;
    std::string expanded_url;
    std::string url;
    std::array<int, 2> indices;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using URL = Objects_template<URL_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_URL_HPP
