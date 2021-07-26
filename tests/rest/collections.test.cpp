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

    // get_collection
    auto const collection_data =
        twitter::get_collection(keys, "custom-539487832448843776");
    network::view_ptree(network::to_ptree(collection_data), std::cout);

    std::cout << twitter::line << "\n\n";

    // find_collections
    auto const collection_ids = twitter::find_collections(keys, "BarackObama");
    network::view_ptree(network::to_ptree(collection_ids), std::cout);

    std::cout << twitter::line << "\n\n";

    // get_collection_info
    auto const collection_info =
        twitter::get_collection_info(keys, "custom-539487832448843776");
    network::view_ptree(network::to_ptree(collection_info), std::cout);

    return 0;
}
