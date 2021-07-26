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

    auto const show_tweet = [](auto const& response) {
        auto const tweet = twitter::parse_tweet(network::to_ptree(response));
        std::cout << to_string(tweet) << twitter::line << "\n" << std::flush;
    };

    try {
        using network::Stream;
        auto const request = twitter::build_sample_stream_request(keys);
        auto const stream  = Stream::launch(request, show_tweet);
        network::wait();
    }
    catch (std::runtime_error const& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
