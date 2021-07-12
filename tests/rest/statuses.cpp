#include <exception>
#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
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

    // update_status
    twitter::update_status(app, "Update Status Test");

    return 0;
}
