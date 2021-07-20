#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    using namespace twitter;

    auto const keys = network::read_credentials("keys");

    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

    // REST API
    // Returns JSON response from twitter.
    std::cout << get_account_settings(keys) << std::endl;

    // Update account's status.
    update_status(keys, "Hello, Twitter!");

    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

    // Streaming API - Connect to Twitter filter stream, tracks "water" text.
    using network::Stream;

    // Track Tweets relating to water.
    auto const parameters = [] {
        auto p = Stream_parameters{};
        p.track.push_back("water");
        p.track.push_back("ocean");
        p.track.push_back("rain");
        p.track.push_back("💧");
        p.track.push_back("🌊");
        p.track.push_back("☔");
        return p;
    }();

    // Invoked each time the search stream receives data.
    auto const show_tweet = [](const auto& response) {
        std::cout << Tweet{response}.text << "\n\n" << std::flush;
    };

    auto const request = build_filtered_stream_request(keys, parameters);
    auto const stream  = Stream::launch(request, show_tweet);

    // Blocking call to allow async strea to be processed indefinitely.
    network::wait();

    return 0;
}
