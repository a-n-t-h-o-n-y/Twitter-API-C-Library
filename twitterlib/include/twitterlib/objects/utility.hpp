#ifndef TWITTERLIB_OBJECTS_UTILITY_HPP
#define TWITTERLIB_OBJECTS_UTILITY_HPP
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

namespace twitter {

/// Return string display of bool \p x.
[[nodiscard]] inline auto to_string(bool x) -> std::string
{
    return x ? "true" : "false";
}

[[nodiscard]] inline auto to_string(std::int64_t x) -> std::string
{
    return std::to_string(x);
}

[[nodiscard]] inline auto to_string(int x) -> std::string
{
    return std::to_string(x);
}

[[nodiscard]] inline auto to_string(float x) -> std::string
{
    return std::to_string(x);
}

template <typename T>
[[nodiscard]] auto to_std(boost::optional<T> const& x) -> std::optional<T>
{
    if (x.has_value())
        return x.value();
    else
        return std::nullopt;
}

inline constexpr auto line =
    "\n────────────────────────────────────────────────────────────────────────"
    "────────";

template <typename T>
[[nodiscard]] auto as_vector(boost::property_tree::ptree const& array)
    -> std::vector<T>
{
    auto result = std::vector<T>{};
    for (auto const& item : array)
        result.push_back(item.second.get_value<T>());
    return result;
}

// array of trees
template <typename T, typename Fn>
[[nodiscard]] auto as_vector(boost::property_tree::ptree const& array,
                             Fn&& parse) -> std::vector<T>
{
    auto result = std::vector<T>{};
    for (auto const& item : array)
        result.push_back(parse(item.second));
    return result;
}

/// Adds 4 spaces after each newline, and at beginning of string.
/** Returns a copy. */
[[nodiscard]] auto add_indention_level(std::string const& x) -> std::string;

}  // namespace twitter
#endif  // TWITTERLIB_OBJECTS_UTILITY_HPP
