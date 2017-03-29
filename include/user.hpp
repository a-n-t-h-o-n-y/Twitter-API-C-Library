#ifndef USER_HPP
#define USER_HPP

#include <cstdint>

namespace tal {

using twitter_id = std::int64_t;

// move coordinates to another header
struct coordinates {
    float lattitude;
    float longitude;
};

}  // namespace tal
#endif  // USER_HPP
