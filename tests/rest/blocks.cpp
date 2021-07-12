#include <exception>
#include <iostream>
#include <vector>

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

    // get_blocked_ids
    std::vector<twitter::Twitter_id> b_ids{twitter::get_blocked_ids(app)};
    // for (twitter::Twitter_id id : b_ids) {
    //     std::cout << id << std::endl;
    // }

    // get_blocked_users
    std::vector<twitter::User> b_users{twitter::get_blocked_users(app)};
    // for (const twitter::User& user : b_users) {
    //     std::cout << user.screen_name << std::endl;
    // }

    return 0;
}
