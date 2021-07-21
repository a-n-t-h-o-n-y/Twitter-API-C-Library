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

    // get_application_rate_limit_status
    // get bearer token before app only auth call.
    auto const bt =
        oauth::get_bearer_token(keys.consumer_key, keys.consumer_secret);
    auto const status = twitter::get_application_rate_limit_status(bt);

    network::view_ptree(network::to_ptree(status), std::cout);

    return 0;
}
