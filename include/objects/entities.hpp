#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <string>
#include <array>
#include <cstdint>
#include <ostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "objects_template.hpp"
#include "objects/hashtag.hpp"
#include "objects/media.hpp"
#include "objects/url.hpp"
#include "objects/user_mention.hpp"

namespace tal {

struct Entities_data {
    explicit operator std::string() const;

    std::vector<Hashtag> hashtags;
    std::vector<Media> media;
    std::vector<URL> urls;
    std::vector<User_mention> user_mentions;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Entities = detail::Objects_template<Entities_data>;

}  // namespace tal
#endif  // ENTITIES_HPP
