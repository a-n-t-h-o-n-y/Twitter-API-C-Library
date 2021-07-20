#include <exception>
#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main() -> int
{
    // Get OAuth keys
    auto const keys = [] {
        try {
            return network::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    // get_account_settings
    auto const settings = twitter::get_account_settings(keys);
    // std::cout << settings << std::endl;

    // verify_credentials
    auto const creds = twitter::verify_credentials(keys);
    // std::cout << creds << std::endl;

    return 0;
}
