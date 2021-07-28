# C++ Twitter API Library

A C++17 library for access to Twitter's Standard v1.1 REST and Streaming APIs.

This library is **not** production ready! It was built in order to learn about
networking and Web APIs.

## Example

```cpp
#include <iostream>
#include <twitterlib/twitterlib.hpp>

int main()
{
    using namespace twitter;

    auto const keys = oauth::read_credentials("keys");

    // REST API
    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

    // Returns JSON response from twitter.
    std::cout << get_account_settings(keys) << std::endl;

    // Update account's status.
    update_status(keys, {"Hello, Twitter!"});

    // Add a reply to an existing Tweet.
    update_status(keys, [] {
        auto p                  = Update_status_parameters{};
        p.message               = "A Reply Tweet";
        p.in_reply_to_status_id = 1405048013278519299;
        return p;
    }());

    // Streaming API
    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

    // Track Tweets relating to water.
    auto const parameters = [] {
        auto p = Stream_parameters{};
        p.track.push_back("water");
        p.track.push_back("ocean");
        p.track.push_back("rain");
        p.track.push_back("💧");
        p.track.push_back("🌊");
        p.track.push_back("☔");
        return p;
    }();

    // Invoked each time the search stream receives data.
    auto const show_tweet = [](auto const& response) {
        std::cout << parse_tweet(network::to_ptree(response)).text << "\n\n"
                  << std::flush;
    };

    auto const request = build_filtered_stream_request(keys, parameters);
    auto const stream  = network::Stream::launch(request, show_tweet);

    // Blocking call to allow async stream to be processed indefinitely.
    network::wait();

    return 0;
}
```

## Build

CMake is the supported build generator, it generates the `twitterlib` library
target that can be linked against.

Other generated target are `twitterlib.demos` and `twitterlib.tests`.

It is recommended to use this library as a git submodule in your project, for
easier version control, though there is an installation target generated.

## Usage

[Register](https://developer.twitter.com/en/apply/user.html) for a Twitter
Developer Account.  Create a new application via the [Twitter App
Dashboard](https://developer.twitter.com/en/apps).  Take a note of the consumer
keys and account secrets on the "Keys and Tokens" tab for your app.

Create a text file called "keys" containing your Twitter API consumer keys and
secrets:

```text
consumer_key *KEY*
consumer_token *TOKEN*
user_token *USERTOKEN*
token_secret *TOKENSECRET*
```

## Library Dependencies

- Boost ASIO >= 1.58
- Boost Property Tree >= 1.58
- OpenSSL >= 1.1
- zlib
