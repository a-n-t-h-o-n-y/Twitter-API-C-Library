#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    // Get OAuth keys
    auto const keys = [] {
        try {
            return oauth::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    // get_favorites
    auto const favorites = twitter::get_favorites(keys, {"thesauruscom"});

    for (auto const& tweet : favorites)
        std::cout << to_string(tweet) << twitter::line << '\n';
    std::cout << std::flush;

    return 0;
}
