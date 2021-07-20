#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <twitterlib/twitterlib.hpp>

auto main(int argc, char* argv[]) -> int
{
    // Parse CL arguments
    if (argc < 2) {
        std::cerr << "usage: get_favorites <twitter-handle> [quantity]\n";
        return 1;
    }
    int quantity{-1};
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
            return network::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    std::vector<twitter::Tweet> twt_vec;
    try {
        twt_vec = twitter::get_favorites(keys, argv[1], quantity);
    }
    catch (...) {
        std::cerr << "Error with request. Twitter handle \'@" << argv[1]
                  << "\' might not exist.\n";
        return 1;
    }
    for (const twitter::Tweet& twt : twt_vec) {
        std::cout << '@' << twt.user_ptr->screen_name << '\n';
        std::cout << twt.text << '\n' << std::endl;
    }

    return 0;
}
