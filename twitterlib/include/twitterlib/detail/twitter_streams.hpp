#ifndef TWITTERLIB_DETAIL_TWITTER_STREAMS_HPP
#define TWITTERLIB_DETAIL_TWITTER_STREAMS_HPP
#include <networklib/request.hpp>

namespace twitter {
namespace detail {

Request twitter_REST_request();
Request twitter_user_stream_request();
Request twitter_filtered_stream_request();
Request twitter_sample_stream_request();
Request twitter_public_stream_request();

}  // namespace detail
}  // namespace twitter
#endif  // TWITTERLIB_DETAIL_TWITTER_STREAMS_HPP
