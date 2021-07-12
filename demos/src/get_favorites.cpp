#include <iostream>
#include <string>
#include <vector>

#include <twitterlib/twitterlib.hpp>

auto main(int argc, char* argv[]) -> int
{
    // Parse CL arguments
    if (argc < 2) {
        std::cout << "usage: get_favorites <twitter-handle> [quantity]"
                  << std::endl;
        return 1;
    }
    int quantity{-1};
    if (argc > 2) {
        try {
            quantity = std::stoi(argv[2]);
        }
        catch (...) {
            std::cout << "Invalid quantity argument." << std::endl;
            return 1;
        }
    }
    // Get OAuth keys
    network::Keys keys;
    try {
        keys = network::read_keys("keys");
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    // Set up App
    twitter::App app{keys.consumer_key, keys.consumer_secret};
    twitter::Account account{keys.user_token, keys.token_secret};
    app.account = account;

    std::vector<twitter::Tweet> twt_vec;
    try {
        twt_vec = get_favorites(app, argv[1], quantity);
    }
    catch (...) {
        std::cout << "Error with request. Twitter handle \'@" << argv[1]
                  << "\' might not exist." << std::endl;
        return 1;
    }
    for (const twitter::Tweet& twt : twt_vec) {
        std::cout << '@' << twt.user_ptr->screen_name << '\n';
        std::cout << twt.text << '\n' << std::endl;
    }

    return 0;
}
