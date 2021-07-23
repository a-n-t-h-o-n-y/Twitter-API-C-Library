#include <twitterlib/objects/utility.hpp>

#include <string>

namespace twitter {

auto add_indention_level(std::string const& x) -> std::string
{
    auto y = std::string(4, ' ');
    for (char c : x) {
        y.push_back(c);
        if (c == '\n')
            y.append(std::string(4, ' '));
    }
    return y;
}

}  // namespace twitter
