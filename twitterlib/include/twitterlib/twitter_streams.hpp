#ifndef TWITTERLIB_TWITTER_STREAM_HPP
#define TWITTERLIB_TWITTER_STREAM_HPP
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include <networklib/request.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/objects/coordinates.hpp>

namespace twitter {

using Twitter_id = std::int64_t;

/// Twitter specific Stream parameters.
/** https://developer.twitter.com/en/docs/twitter-api/v1/tweets/filter-realtime/guides/basic-stream-parameters*/
struct Stream_parameters {
    std::string delimited;
    bool stall_warnings{false};
    std::vector<std::string> track;
    std::vector<std::pair<Earth_coordinates, Earth_coordinates>> locations;
    std::string language;
    std::vector<Twitter_id> follow;
    std::string filter_level;
    std::int16_t count;
};

/// Build a Request for a Twitter Filtered Stream; for use with network::Stream.
[[nodiscard]] auto build_filtered_stream_request(
    oauth::Credentials const& keys,
    Stream_parameters parameters = {}) -> network::Request;

/// Build a Request for a Twitter Sample Stream; for use with network::Stream.
[[nodiscard]] auto build_sample_stream_request(
    oauth::Credentials const& keys,
    Stream_parameters parameters = {}) -> network::Request;

}  // namespace twitter
#endif  // TWITTERLIB_TWITTER_STREAM_HPP
