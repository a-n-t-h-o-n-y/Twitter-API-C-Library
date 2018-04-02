# C++ Twitter API Library
A work in progress library for access to Twitter's REST and Streaming APIs.
```c++
#include <iostream>
#include <twitterlib/twitterlib.hpp>

int main() {
    network::Keys keys{network::read_keys("keys")};

    twitter::App app{keys.consumer_key, keys.consumer_secret};
    twitter::Account account{keys.user_token, keys.token_secret};

    app.account = account;

    // REST API - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Returns JSON response from twitter.
    std::cout << get_account_settings(app) << std::endl;

    // Update account's status.
    update_status("Hello, Twitter!");

    // Streaming API - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Connect to Twitter filter stream, tracks "Seach Term" text.
    app.filtered_stream.parameters().track.push_back("Search Term");

    // Function that will be called on each response from the stream.
    app.filtered_stream.register_function([](const auto& response) {
        std::cout << twitter::Tweet(response).text << std::endl;
    });
    // Open the stream
    app.filtered_stream.open();

    // Blocking call to allow async stream to be processed indefinitely.
    twitter::Twitter_stream::wait();

    return 0;
}
```

### Library Dependencies
* Boost ASIO >= 1.58
* Boost Property Tree >= 1.58
* OpenSSL
* zlib

