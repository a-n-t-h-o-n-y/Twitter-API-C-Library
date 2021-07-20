#include <exception>
#include <iostream>

#include <twitterlib/twitterlib.hpp>

auto main(int argc, char* argv[]) -> int
{
    if (argc < 2) {
        std::cout << "usage: search <search-term>" << std::endl;
        return 1;
    }
    auto const keys = [] {
        try {
            return network::read_credentials("keys");
        }
        catch (std::invalid_argument const& e) {
            std::cerr << e.what() << '\n';
            std::exit(1);
        }
    }();

    // TODO new api
    // app.filtered_stream.parameters().track.push_back(argv[1]);
    // app.filtered_stream.register_function([](const auto& response) {
    //     twitter::Tweet twt{response};
    //     std::cout << twt.user_ptr->name;
    //     std::cout << " (@" << twt.user_ptr->screen_name << ")" << std::endl;
    //     std::cout << twt.created_at << std::endl;
    //     std::cout << twt.text << '\n' << std::endl;
    // });

    // should be:
    // auto parameters = build_filtered_stream_parameters();
    // parameters.app_credentials = {key, secret};
    // parameters.account_credentials = {key, secret};
    // bearer token?
    // parameters.track.push_back(argv[1]);
    // auto callbacks = Callbacks{{[](const auto& response) {
    //     auto twt = twitter::Tweet{response};
    //     std::cout << twt.user_ptr->name;
    //     std::cout << " (@" << twt.user_ptr->screen_name << ")" << std::endl;
    //     std::cout << twt.created_at << std::endl;
    //     std::cout << twt.text << '\n' << std::endl;}
    // }};
    try {
        // auto const stream = launch_filtered_stream(parameters, callbacks);
        // ^^ Creates and connects to filtered stream
        // app.filtered_stream.open();
        // twitter::Twitter_stream::wait();
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
