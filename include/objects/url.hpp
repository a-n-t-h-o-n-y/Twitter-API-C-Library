#ifndef URL_HPP
#define URL_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace tal {

struct URL {
    URL() = default;
    explicit URL(const std::string& json);
    explicit URL(const boost::property_tree::ptree& tree);

    std::string display_url;
    std::string expanded_url;
    std::string url;
    std::array<int, 2> indices;

   private:
    void construct(const boost::property_tree::ptree& tree);
};
}  // namespace tal
#endif  // URL_HPP
