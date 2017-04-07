#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <string>
#include <array>
#include <cstdint>
#include <ostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "objects/hashtag.hpp"
#include "objects/media.hpp"
#include "objects/url.hpp"
#include "objects/user_mention.hpp"

namespace tal {

struct Entities {
    Entities() = default;
    explicit Entities(const std::string& json);
    explicit Entities(const boost::property_tree::ptree& tree);

    explicit operator std::string() const;

    std::vector<Hashtag> hashtags;
    std::vector<Media> media;
    std::vector<URL> urls;
    std::vector<User_mention> user_mentions;

   private:
    void construct(const boost::property_tree::ptree& tree);
};

inline std::ostream& operator<<(std::ostream& os, const Entities& media) {
    return os << static_cast<std::string>(media);
}
}  // namespace tal
#endif  // ENTITIES_HPP
