#ifndef TWITTERLIB_OBJECTS_HASHTAG_HPP
#define TWITTERLIB_OBJECTS_HASHTAG_HPP
#include <array>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

struct Hashtag_data {
    explicit operator std::string() const;

    std::string text;
    std::array<int, 2> indices;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Hashtag = Objects_template<Hashtag_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_HASHTAG_HPP
