#ifndef TWITTERLIB_DETAIL_TO_STRING_HPP
#define TWITTERLIB_DETAIL_TO_STRING_HPP
#include <ios>
#include <sstream>
#include <string>

namespace twitter::detail {

template <typename T>
auto to_string(T const& x) -> std::string
{
    auto ss = std::ostringstream{};
    ss << std::boolalpha << x;
    return ss.str();
}

}  // namespace twitter::detail
#endif  // TWITTERLIB_DETAIL_TO_STRING_HPP
