#ifndef MEDIA_HPP
#define MEDIA_HPP

#include <string>
#include <array>
#include <cstdint>
#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include "sizes.hpp"
#include "objects_template.hpp"

namespace tal {

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

using Media = detail::Objects_template<Media_data>;

}  // namespace tal
#endif  // MEDIA_HPP
