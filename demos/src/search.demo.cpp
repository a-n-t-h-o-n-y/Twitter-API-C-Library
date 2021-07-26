#include <cstdlib>
#include <exception>
#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main(int argc, char* argv[]) -> int
{
    if (argc < 2) {
        std::cerr << "Usage: search <search-term> ...\n";
        return 1;
    }
    auto const keys = [] {
        try {
            return oauth::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    auto const parameters = [&] {
        auto p = twitter::Stream_parameters{};
        for (auto i = 1; i < argc; ++i)
            p.track.push_back(argv[i]);
        return p;
    }();

    auto const show_tweet = [](auto const& response) {
        auto const tweet = twitter::parse_tweet(network::to_ptree(response));
        std::cout << tweet.user.name;
        std::cout << " (@" << tweet.user.screen_name << ")\n";
        std::cout << tweet.created_at << '\n';
        std::cout << tweet.text << "\n\n" << std::flush;
    };

    auto const request = build_filtered_stream_request(keys, parameters);

    try {
        auto const stream = network::Stream::launch(request, show_tweet);
        network::wait();
    }
    catch (std::runtime_error const& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
