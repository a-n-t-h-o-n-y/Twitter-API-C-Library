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

    // get_account_settings
    auto const settings = twitter::get_account_settings(keys);
    network::view_ptree(network::to_ptree(settings), std::cout);

    auto const brk = "\n\n────────────────────────────────────────────────\n\n";
    std::cout << brk;

    // verify_credentials
    auto const creds = twitter::verify_credentials(keys);
    network::view_ptree(network::to_ptree(creds), std::cout);

    return 0;
}
