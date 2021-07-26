#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

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

    // get_blocked_ids
    auto const ids = twitter::get_blocked_ids(keys);
    for (auto const id : ids)
        std::cout << id << '\n';

    std::cout << twitter::line << "\n\n";

    // get_blocked_users
    auto const users = twitter::get_blocked_users(keys);
    for (auto const& user : users)
        std::cout << user.screen_name << '\n';

    std::cout << std::flush;

    return 0;
}
