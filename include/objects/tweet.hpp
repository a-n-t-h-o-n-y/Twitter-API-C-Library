#ifndef TWEET_HPP
#define TWEET_HPP

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>
#include "objects_template.hpp"

namespace tal {

struct Tweet_data {
    explicit operator std::string() const;

   protected:
    void construct(const boost::property_tree::ptree& tree);
};

using Tweet = detail::Objects_template<Tweet_data>;

}  // namespace tal
#endif  // TWEET_HPP
