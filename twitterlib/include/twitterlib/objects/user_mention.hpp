#ifndef TWITTERLIB_OBJECTS_USER_MENTION_HPP
#define TWITTERLIB_OBJECTS_USER_MENTION_HPP
#include <array>
#include <cstdint>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>

namespace twitter {

struct User_mention_data {
    explicit operator std::string() const;

    std::int64_t id;
    std::string id_str;
    std::array<int, 2> indices;
    std::string name;
    std::string screen_name;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using User_mention = Objects_template<User_mention_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_USER_MENTION_HPP
