#ifndef DETAIL_USER_MENTION_HPP
#define DETAIL_USER_MENTION_HPP

#include <string>
#include <cstdint>
#include <array>
#include <boost/property_tree/ptree.hpp>
#include "objects_template.hpp"

namespace tal {

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

using User_mention = detail::Objects_template<User_mention_data>;

}  // namespace tal
#endif  // DETAIL_USER_MENTION_HPP
