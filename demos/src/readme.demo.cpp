#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    using namespace twitter;

    auto const keys = oauth::read_credentials("keys");

    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

    // REST API
    // Returns JSON response from twitter.
    std::cout << get_account_settings(keys) << std::endl;

    // Update account's status.
    update_status(keys, {"Hello, Twitter!"});

    // Add a reply to an existing Tweet.
    update_status(keys, [] {
        auto p                  = Update_status_parameters{};
        p.message               = "A Reply Tweet";
        p.in_reply_to_status_id = 1405048013278519299;
        return p;
    }());

    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    // Streaming API - Connect to Twitter filter stream, tracks "water" text.

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
    auto const show_tweet = [](auto const& response) {
        std::cout << parse_tweet(network::to_ptree(response)).text << "\n\n"
                  << std::flush;
    };

    auto const request = build_filtered_stream_request(keys, parameters);
    auto const stream  = network::Stream::launch(request, show_tweet);

    // Blocking call to allow async stream to be processed indefinitely.
    network::wait();

    return 0;
}
