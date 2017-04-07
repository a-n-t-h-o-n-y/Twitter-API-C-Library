#ifndef MEDIA_HPP
#define MEDIA_HPP

#include <string>
#include <array>
#include <cstdint>
#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include "objects/sizes.hpp"

namespace tal {

struct Media {
    Media() = default;
    explicit Media(const std::string& json);
    explicit Media(const boost::property_tree::ptree& tree);

    explicit operator std::string() const;

    std::string display_url;
    std::string expanded_url;
    std::int64_t id;
    std::string id_str;
    std::array<int, 2> indices;
    std::string media_url;
    std::string media_url_https;
    Sizes sizes;
    std::int64_t source_status_id;
    std::string source_status_id_str;
    std::string type;
    std::string url;

   private:
    void construct(const boost::property_tree::ptree& tree);
};

inline std::ostream& operator<<(std::ostream& os, const Media& media) {
    return os << static_cast<std::string>(media);
}
}  // namespace tal
#endif  // MEDIA_HPP
