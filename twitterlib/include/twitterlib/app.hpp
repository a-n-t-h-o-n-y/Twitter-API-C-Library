#ifndef TWITTERLIB_APP_HPP
#define TWITTERLIB_APP_HPP
#include <string>
#include <utility>

#include <twitterlib/account.hpp>
#include <twitterlib/twitter_stream.hpp>

namespace twitter {

struct App {
    std::string consumer_key;
    std::string consumer_secret;

    Account account;
    std::string bearer_token;

    Twitter_stream user_stream{this, build_user_stream_parameters()};
    Twitter_stream filtered_stream{this, build_filtered_stream_parameters()};
    Twitter_stream sample_stream{this, build_sample_stream_parameters()};
};

}  // namespace twitter
#endif  // TWITTERLIB_APP_HPP
