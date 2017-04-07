#ifndef USER_MENTION_HPP
#define USER_MENTION_HPP

#include <string>
#include <cstdint>
#include <array>
#include <boost/property_tree/ptree.hpp>

namespace tal {

struct User_mention {
    User_mention() = default;
    explicit User_mention(const std::string& json);
    explicit User_mention(const boost::property_tree::ptree& tree);

    std::int64_t id;
    std::string id_str;
    std::array<int, 2> indices;
    std::string name;
    std::string screen_name;

   private:
    void construct(const boost::property_tree::ptree& tree);
};

}  // namespace tal
#endif  // USER_MENTION_HPP
