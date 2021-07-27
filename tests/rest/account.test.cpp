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

    {  // get_account_settings
        auto const x = twitter::get_account_settings(keys);
        network::view_ptree(network::to_ptree(x), std::cout);
    }

    std::cout << twitter::line << "\n\n";

    {  // verify_credentials_JSON
        auto const x = twitter::verify_credentials_JSON(keys);
        network::view_ptree(network::to_ptree(x), std::cout);
    }

    std::cout << twitter::line << "\n\n";

    {  // verify_credentials
        auto const x = twitter::verify_credentials(keys, [] {
            auto p             = twitter::Verify_credentials_parameters{};
            p.include_entities = true;
            p.skip_status      = true;
            p.include_email    = false;
            return p;
        }());
        std::cout << to_string(x) << '\n';
    }

    std::cout << twitter::line << "\n\n";

    {  // get_profile_banner
        auto const x = twitter::get_profile_banner(keys, {"thesauruscom"});
        network::view_ptree(network::to_ptree(x), std::cout);
    }

    // std::cout << twitter::line << "\n\n";

    // CAREFUL
    // {  // remove_profile_banner
    //     twitter::remove_profile_banner(keys);
    // }

    // {  // update_account
    //     twitter::update_account(keys);
    // }

    // {  // create_saved_search
    //     auto const x = twitter::create_saved_search(keys, "water");
    //     network::view_ptree(network::to_ptree(x), std::cout);
    // }

    // std::int64_t id = 0;
    // {  // get_saved_searches
    //     auto const x     = twitter::get_saved_searches(keys);
    //     auto const ptree = network::to_ptree(x);
    //     for (auto const& tree : ptree)
    //         id = tree.second.get<std::int64_t>("id");
    //     network::view_ptree(ptree, std::cout);
    // }

    // {  // get_saved_search_info
    //     auto const x = twitter::get_saved_search_info(keys, id);
    //     network::view_ptree(network::to_ptree(x), std::cout);
    // }

    // {  // destroy_saved_search()
    //     auto const x = twitter::destroy_saved_search(keys, id);
    //     network::view_ptree(network::to_ptree(x), std::cout);
    // }

    // {  // update_profile
    //     auto const x = twitter::update_profile(keys);
    //     network::view_ptree(network::to_ptree(x), std::cout);
    // }

    return 0;
}
