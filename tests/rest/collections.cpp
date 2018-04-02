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

    // get_collection
    network::Response collection_data{
        twitter::get_collection(app, "custom-539487832448843776")};
    // network::view_ptree(collection_data.ptree());

    network::Response collection_ids{
        twitter::find_collections(app, "BarackObama")};
    // network::view_ptree(collection_ids.ptree());

    network::Response collection_info{
        twitter::get_collection_info(app, "custom-539487832448843776")};
    // network::view_ptree(collection_info.ptree());

    return 0;
}
