#ifndef TWITTERLIB_DETAIL_TYPES_HPP
#define TWITTERLIB_DETAIL_TYPES_HPP
#include <stdexcept>
#include <string>

namespace twitter {

enum class Sleep_time { Enabled, Disabled };

/// Hour of the day (0-23). Constructor can throw std::invalid_argument.
class Hour {
   public:
    explicit Hour(int time_of_day_) : time_of_day{validate(time_of_day_)} {}

   public:
    int time_of_day;

   private:
    [[nodiscard]] static auto validate(int const t) -> int
    {
        if (t >= 0 && t <= 23)
            return t;
        throw std::invalid_argument{"Hour must be in range [0, 23]."};
    }
};

/// Hex color value, can be either 3 or 6 characters long.
class Hex_color {
   public:
    explicit Hex_color(std::string const& hex_value)
        : color{validate(hex_value)}
    {}

   public:
    std::string color;

   private:
    [[nodiscard]] static auto validate(std::string const& c)
        -> std::string const&
    {
        if (c.size() == 3 || c.size() == 6)
            return c;
        throw std::invalid_argument{"Hex_color must be 3 or 5 chars long."};
    }
};

}  // namespace twitter
#endif  // TWITTERLIB_DETAIL_TYPES_HPP
