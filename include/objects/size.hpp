#ifndef SIZE_HPP
#define SIZE_HPP

#include <string>
#include <ostream>
#include <boost/property_tree/ptree.hpp>

namespace tal {

struct Size {
    Size() = default;
    explicit Size(const std::string& json);
    explicit Size(const boost::property_tree::ptree& tree);

    explicit operator std::string() const;

    int height;
    int width;
    std::string resize;

   private:
    void construct(const boost::property_tree::ptree& tree);
};

inline std::ostream& operator<<(std::ostream& os, const Size& size) {
    return os << static_cast<std::string>(size);
}

}  // namespace tal
#endif  // SIZE_HPP
