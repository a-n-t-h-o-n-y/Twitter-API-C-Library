#ifndef TWITTERLIB_OBJECTS_MEDIA_HPP
#define TWITTERLIB_OBJECTS_MEDIA_HPP
#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/sizes.hpp>

namespace twitter {

struct Media_data {
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

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Media = Objects_template<Media_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_MEDIA_HPP
