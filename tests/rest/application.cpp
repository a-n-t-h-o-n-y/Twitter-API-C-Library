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

    // get_application_rate_limit_status
    network::Response status{twitter::get_application_rate_limit_status(app)};
    network::view_ptree(status.ptree());

    return 0;
}
