#ifndef TWITTERLIB_TWITTER_STREAM_HPP
#define TWITTERLIB_TWITTER_STREAM_HPP
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/stream.hpp>
#include <twitterlib/objects/coordinates.hpp>

namespace twitter {
struct App;

using Twitter_id = std::int64_t;

struct Stream_parameters {
    std::string delimited;
    bool stall_warnings{false};
    std::vector<std::string> track;
    std::pair<Coordinates, Coordinates> locations;
    bool use_locations_{false};

    std::string language;
    std::vector<Twitter_id> follow;
    std::string filter_level;
    std::int16_t count;

    // User Stream Only
    std::string with;
    std::string replies;
    bool stringify_friend_ids{false};

    // Request Parameters
    std::string host;
    std::string URI;
    std::string method;
    std::string content_type{"application/json"};
};

Stream_parameters build_user_stream_parameters();

Stream_parameters build_filtered_stream_parameters();

Stream_parameters build_sample_stream_parameters();

class Twitter_stream {
   public:
    using Callback = std::function<void(const network::Response&)>;
    using Condition = std::function<bool(const network::Response&)>;

    Twitter_stream(const App* app, const Stream_parameters& params);

    void register_function(Callback f1,
                           Condition f2 = [](const network::Response&) {
                               return true;
                           });

    void open();

    void close();

    // builds request, sets stream_.request, stream_.reconnect();
    void reconnect();

    Stream_parameters& parameters();
    const Stream_parameters& parameters() const;

    static void wait();

   private:
    const App* const app_;
    network::Stream stream_;
    Stream_parameters params_;

    network::Request build_request();
    network::Request parameters_to_request(const Stream_parameters& params);
    void insert_user_parameters(network::Request& r,
                                const Stream_parameters& params);
};

}  // namespace twitter
#endif  // TWITTERLIB_TWITTER_STREAM_HPP
