#include <exception>
#include <iostream>
#include <vector>

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

    // get_blocked_ids
    auto const b_ids = twitter::get_blocked_ids(keys);
    // for (twitter::Twitter_id id : b_ids) {
    //     std::cout << id << std::endl;
    // }

    // get_blocked_users
    auto const b_users = twitter::get_blocked_users(keys);
    // for (const twitter::User& user : b_users) {
    //     std::cout << user.screen_name << std::endl;
    // }

    return 0;
}
