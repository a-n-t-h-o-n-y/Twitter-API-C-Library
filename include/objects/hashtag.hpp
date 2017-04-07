#ifndef HASHTAG_HPP
#define HASHTAG_HPP

#include <string>
#include <array>
#include <boost/property_tree/ptree.hpp>

namespace tal {

struct Hashtag {
    Hashtag() = default;
    explicit Hashtag(const std::string& json);
    explicit Hashtag(const boost::property_tree::ptree& tree);

    std::string text;
    std::array<int, 2> indices;

    private:
    void construct(const boost::property_tree::ptree& tree);
};

}  // namespace tal
#endif  // HASHTAG_HPP
