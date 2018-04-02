#include <exception>
#include <iostream>
#include <vector>

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

    // get_favorites
    std::vector<twitter::Tweet> bo_favs{
        twitter::get_favorites(app, "BarackObama")};
    // for (const twitter::Tweet& twt : bo_favs) {
    //     std::cout << twt.text << std::endl;
    // }

    return 0;
}
