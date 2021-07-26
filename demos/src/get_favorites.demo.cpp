#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <twitterlib/twitterlib.hpp>

auto main(int argc, char* argv[]) -> int
{
    // Parse CL arguments
    if (argc < 2) {
        std::cerr << "Usage: get_favorites <twitter-handle> [quantity]\n";
        return 1;
    }
    auto quantity = -1;
    if (argc > 2) {
        try {
            quantity = std::stoi(argv[2]);
        }
        catch (...) {
            std::cerr << "Invalid quantity argument.\n";
            return 1;
        }
    }

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

    auto tweets = std::vector<twitter::Tweet>{};
    try {
        tweets = twitter::get_favorites(keys, argv[1], quantity);
    }
    catch (...) {
        std::cerr << "Error with request. Twitter handle \'@" << argv[1]
                  << "\' might not exist.\n";
        return 1;
    }
    for (auto const& tweet : tweets) {
        std::cout << '@' << tweet.user.screen_name << '\n';
        std::cout << tweet.text << '\n' << std::endl;
    }

    return 0;
}
