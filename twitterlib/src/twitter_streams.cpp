#include <twitterlib/twitter_streams.hpp>

#include <cstdint>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/wait.hpp>
#include <twitterlib/objects/coordinates.hpp>

namespace {
using namespace twitter;

struct Stream_request_data {
    Stream_parameters stream_parameters;

    // Request Parameters
    std::string host;
    std::string URI;
    std::string method;
    std::string content_type{"application/json"};
};

[[nodiscard]] auto build_filtered_stream_parameters(
    Stream_parameters stream_params) -> Stream_request_data
{
    auto filtered_params              = Stream_request_data{};
    filtered_params.stream_parameters = std::move(stream_params);
    filtered_params.host              = "stream.twitter.com";
    filtered_params.URI               = "/1.1/statuses/filter.json";
    filtered_params.method            = "POST";
    return filtered_params;
}

[[nodiscard]] auto build_sample_stream_parameters(
    Stream_parameters stream_params) -> Stream_request_data
{
    auto sample_params              = Stream_request_data{};
    sample_params.stream_parameters = std::move(stream_params);
    sample_params.host              = "stream.twitter.com";
    sample_params.URI               = "/1.1/statuses/sample.json";
    sample_params.method            = "GET";
    return sample_params;
}

/// Only builds the shared parameters.
auto parameters_to_request(Stream_request_data const& params)
    -> network::Request
{
    auto r         = network::Request{};
    r.host         = params.host;
    r.URI          = params.URI;
    r.HTTP_method  = params.method;
    r.content_type = "application/json";

    auto const& stream_params = params.stream_parameters;

    if (!params.stream_parameters.delimited.empty())
        r.queries.push_back({"delimited", stream_params.delimited});

    r.queries.push_back(
        {"stall_warnings", stream_params.stall_warnings ? "true" : "false"});

    if (!stream_params.track.empty()) {
        auto ss    = std::ostringstream{};
        auto comma = std::string{};
        for (auto const& str : stream_params.track) {
            ss << comma << str;
            comma = ",";
        }
        r.queries.push_back({"track", ss.str()});
    }

    if (stream_params.locations.has_value()) {
        auto ss = std::ostringstream{};
        ss << stream_params.locations->first.longitude << ',';
        ss << stream_params.locations->first.latitude << ',';
        ss << stream_params.locations->second.longitude << ',';
        ss << stream_params.locations->second.latitude;
        r.queries.push_back({"locations", ss.str()});
    }

    if (!stream_params.follow.empty()) {
        auto ss    = std::ostringstream{};
        auto comma = std::string{};
        for (auto const& id : stream_params.follow) {
            ss << comma << id;
            comma = ",";
        }
        r.queries.push_back({"follow", ss.str()});
    }

    return r;
}

}  // namespace

namespace twitter {

auto build_filtered_stream_request(network::Credentials const& keys,
                                   Stream_parameters parameters)
    -> network::Request
{
    auto request = parameters_to_request(
        build_filtered_stream_parameters(std::move(parameters)));
    network::authorize(request, keys);
    return request;
}

auto build_sample_stream_request(network::Credentials const& keys,
                                 Stream_parameters parameters)
    -> network::Request
{
    auto request = parameters_to_request(
        build_sample_stream_parameters(std::move(parameters)));
    network::authorize(request, keys);
    return request;
}

}  // namespace twitter
