#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    network::Keys keys{network::read_keys("keys")};

    twitter::App app{keys.consumer_key, keys.consumer_secret};
    twitter::Account account{keys.user_token, keys.token_secret};

    app.account = account;

    // REST API - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Returns JSON response from twitter.
    std::cout << get_account_settings(app) << std::endl;

    // Update account's status.
    update_status(app, "Hello, Twitter!");

    // Streaming API - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Connect to Twitter filter stream, tracks "Search Term" text.
    app.filtered_stream.parameters().track.push_back("Search Term");

    // Function that will be called on each response from the stream.
    app.filtered_stream.register_function([](const auto& response) {
        std::cout << twitter::Tweet(response).text << std::endl;
    });
    // Open the stream
    app.filtered_stream.open();

    // Blocking call to allow async stream to be processed indefinitely.
    twitter::Twitter_stream::wait();

    return 0;
}
