#ifndef OBJECTS_TEMPLATE_HPP
#define OBJECTS_TEMPLATE_HPP

#include <string>
#include <sstream>
#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../message.hpp"

namespace tal {
namespace detail {

template <typename T>
class Objects_template : public T {
   public:
    Objects_template() = default;
    explicit Objects_template(const std::string json) {
        T::construct(string_to_ptree(json));
    }
    explicit Objects_template(const boost::property_tree::ptree& tree) {
        T::construct(tree);
    }
    explicit Objects_template(const Message& m) {
        T::construct(string_to_ptree(m.json()));
    }

    explicit operator std::string() const { return T::operator std::string(); }

   private:
    boost::property_tree::ptree string_to_ptree(const std::string& json) {
        std::stringstream ss{json};
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(ss, tree);
        return tree;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Objects_template<T>& o) {
    return os << static_cast<std::string>(o);
    // possibly downcast to T* here or up^
}

}  // namespace detail
}  // namespace tal
#endif  // OBJECTS_TEMPLATE_HPP
