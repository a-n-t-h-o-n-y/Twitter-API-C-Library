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

    // get_account_settings
    network::Response settings{twitter::get_account_settings(app)};
    // std::cout << settings << std::endl;

    // verify_credentials
    network::Response creds{twitter::verify_credentials(app)};
    // std::cout << creds << std::endl;

    return 0;
}
