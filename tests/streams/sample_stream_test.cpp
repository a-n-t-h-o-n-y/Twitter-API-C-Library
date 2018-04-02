#include <exception>
#include <iostream>
#include <twitterlib/twitterlib.hpp>

int main() {
    // Get OAuth keys
    network::Keys keys;
    try {
        keys = network::read_keys("keys");
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    // Set up App
    twitter::App app{keys.consumer_key, keys.consumer_secret};
    twitter::Account account{keys.user_token, keys.token_secret};
    app.account = account;

    app.sample_stream.register_function([](const auto& response) {
        twitter::Tweet twt{response};
        if (!twt.text.empty()) {
            std::cout << twt.text << '\n' << std::endl;
        }
    });

    try {
        app.sample_stream.open();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    twitter::Twitter_stream::wait();

    return 0;
}
