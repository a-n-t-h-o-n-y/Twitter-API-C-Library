#include <cstdlib>
#include <exception>
#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    // Get OAuth keys
    auto const keys = [] {
        try {
            return oauth::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    auto const parameters = [] {
        auto p = twitter::Stream_parameters{};
        p.track.push_back("water");
        return p;
    }();

    auto const show_tweet = [](auto const& response) {
        std::cout << twitter::Tweet{response}.text << "\n\n" << std::flush;
    };

    try {
        using network::Stream;
        auto const request = build_filtered_stream_request(keys, parameters);
        auto const stream  = Stream::launch(request, show_tweet);
        network::wait();
    }
    catch (std::runtime_error const& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
