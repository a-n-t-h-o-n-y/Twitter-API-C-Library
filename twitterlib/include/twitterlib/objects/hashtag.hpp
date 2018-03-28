#ifndef TWITTERLIB_OBJECTS_HASHTAG_HPP
#define TWITTERLIB_OBJECTS_HASHTAG_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>

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
#endif  // TWITTERLIB_OBJECTS_HASHTAG_HPP
