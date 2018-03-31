#include <exception>
#include <iostream>

#include <twitterlib/twitterlib.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage: search <search-term>" << std::endl;
        return 1;
    }
    network::Keys keys;
    try {
        keys = network::read_keys("keys");
    } catch (std::invalid_argument e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    twitter::App app{keys.consumer_key, keys.consumer_secret};
    twitter::Account account{keys.user_token, keys.token_secret};

    app.set_account(account);

    app.filtered_stream.parameters().track.push_back(argv[1]);
    app.filtered_stream.register_function([](const auto& message) {
        twitter::Tweet twt{message};
        std::cout << twt.user_ptr->name;
        std::cout << " (@" << twt.user_ptr->screen_name << ")" << std::endl;
        std::cout << twt.created_at << std::endl;
        std::cout << twt.text << '\n' << std::endl;
    });

    try {
        app.filtered_stream.open();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    twitter::Twitter_stream::wait();

    return 0;
}
