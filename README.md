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
    // Returns JSON response from Twitter.
    std::cout << get_account_settings(app) << std::endl;

    // Update account's status.
    update_status(app, "Hello, Twitter!");

    // Streaming API - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Connect to Twitter filter stream, tracks "Search Term" text.
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

## Build / compile

Use `cmake .` to generate the build environment.

Once successful, run `make && make demos` to build the libraries and the demo apps.

## Usage

[Register](https://developer.twitter.com/en/apply/user.html) for a Twitter Developer Account.
Create a new application via the [Twitter App Dashboard](https://developer.twitter.com/en/apps).
Take a note of the consumer keys and account secrets on the "Keys and Tokens" tab for your app.

Create a text file called "keys" containing your Twitter API consumer keys and secrets:

```text
consumer_key *KEY*
consumer_token *TOKEN*
user_token *USERTOKEN*
token_secret *TOKENSECRET*
```

Run the demo apps.

### Library Dependencies

* Boost ASIO >= 1.58
* Boost Property Tree >= 1.58
* OpenSSL >= 1.1
* zlib
