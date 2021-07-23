#include <twitterlib/twitter_streams.hpp>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/wait.hpp>
#include <oauth/authorize.hpp>
#include <twitterlib/objects/coordinates.hpp>
#include <twitterlib/objects/utility.hpp>

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
        auto params = std::string{};
        auto comma  = std::string{};
        for (auto const& str : stream_params.track) {
            params.append(comma).append(str);
            comma = ",";
        }
        r.queries.push_back({"track", std::move(params)});
    }

    {
        auto list = std::string{};
        for (auto const& location : stream_params.locations) {
            list.append(to_string(location.first.longitude)).append(1, ',');
            list.append(to_string(location.first.latitude)).append(1, ',');
            list.append(to_string(location.second.longitude)).append(1, ',');
            list.append(to_string(location.second.latitude)).append(1, ',');
        }
        if (!list.empty())
            list.pop_back();
        r.queries.push_back({"locations", list});
    }

    if (!stream_params.follow.empty()) {
        auto params = std::string{};
        auto comma  = std::string{};
        for (auto const& id : stream_params.follow) {
            params.append(comma).append(to_string(id));
            comma = ",";
        }
        r.queries.push_back({"follow", std::move(params)});
    }

    return r;
}

}  // namespace

namespace twitter {

auto build_filtered_stream_request(oauth::Credentials const& keys,
                                   Stream_parameters parameters)
    -> network::Request
{
    auto request = parameters_to_request(
        build_filtered_stream_parameters(std::move(parameters)));
    authorize(request, keys);
    return request;
}

auto build_sample_stream_request(oauth::Credentials const& keys,
                                 Stream_parameters parameters)
    -> network::Request
{
    auto request = parameters_to_request(
        build_sample_stream_parameters(std::move(parameters)));
    authorize(request, keys);
    return request;
}

}  // namespace twitter
