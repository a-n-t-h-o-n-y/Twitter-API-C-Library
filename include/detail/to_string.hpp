#ifndef TO_STRING_HPP
#define TO_STRING_HPP

#include <string>
#include <sstream>
#include <ios>

namespace tal {
namespace detail {

template <typename T>
std::string to_string(const T& thing) {
    std::stringstream ss;
    ss << std::boolalpha << thing;
    return ss.str();
}

}  // namespace detail
}  // namespace tal
#endif  // TO_STRING_HPP
