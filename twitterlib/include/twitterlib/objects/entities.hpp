#ifndef TWITTERLIB_OBJECTS_ENTITIES_HPP
#define TWITTERLIB_OBJECTS_ENTITIES_HPP
#include <array>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/hashtag.hpp>
#include <twitterlib/objects/media.hpp>
#include <twitterlib/objects/objects_template.hpp>
#include <twitterlib/objects/url.hpp>
#include <twitterlib/objects/user_mention.hpp>

namespace twitter {

class Entities_data {
   public:
    std::vector<Hashtag> hashtags;
    std::vector<Media> media;
    std::vector<URL> urls;
    std::vector<User_mention> user_mentions;

   public:
    explicit operator std::string() const;

   protected:
    void construct(boost::property_tree::ptree const& tree);
};

using Entities = Objects_template<Entities_data>;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_ENTITIES_HPP
