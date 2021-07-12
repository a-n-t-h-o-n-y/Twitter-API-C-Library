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

    app.filtered_stream.parameters().track.push_back("water");
    app.filtered_stream.register_function([](const auto& response) {
        twitter::Tweet twt{response};
        std::cout << twt.text << '\n' << std::endl;
    });

    try {
        app.filtered_stream.open();
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    twitter::Twitter_stream::wait();

    return 0;
}
