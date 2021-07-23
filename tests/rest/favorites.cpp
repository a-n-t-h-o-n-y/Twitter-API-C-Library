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

    auto const brk = "\n\n────────────────────────────────────────────────\n\n";

    // get_favorites
    auto const favorites = twitter::get_favorites(keys, "thesauruscom");

    for (auto const& tweet : favorites)
        std::cout << to_string(tweet) << brk;
    std::cout << std::flush;

    return 0;
}
