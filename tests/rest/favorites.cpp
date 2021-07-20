#include <exception>
#include <iostream>
#include <vector>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    // Get OAuth keys
    auto const keys = [] {
        try {
            return network::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    // get_favorites
    auto const bo_favs = twitter::get_favorites(keys, "BarackObama");

    // for (const twitter::Tweet& twt : bo_favs) {
    //     std::cout << twt.text << std::endl;
    // }

    return 0;
}
