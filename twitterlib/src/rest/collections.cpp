#include <twitterlib/rest/collections.hpp>

#include <optional>
#include <stdexcept>
#include <string>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/detail/utility.hpp>

namespace twitter {

auto get_collection(oauth::Credentials const& keys,
                    Get_collection_parameters const& p) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/collections/entries.json";

    r.queries.push_back({"id", p.id});

    if (p.count.has_value())
        r.queries.push_back({"count", to_string(p.count.value())});

    if (p.max_position.has_value())
        r.queries.push_back(
            {"max_position", to_string(p.max_position.value())});

    if (p.min_position.has_value())
        r.queries.push_back(
            {"min_position", to_string(p.min_position.value())});

    authorize(r, keys);

    return https_read(https_write(r));
}

auto find_collections(oauth::Credentials const& keys,
                      Find_collections_parameters const& p) -> network::Response
{
    using namespace network;

    if (!p.screen_name.has_value() && !p.user_id.has_value()) {
        throw std::invalid_argument{
            "find_collections must provide either screen_name or user_id"};
    }

    auto result = network::Response{};

    auto cursor = std::string{"-1"};
    while (cursor != "0") {
        auto r        = Request{};
        r.HTTP_method = "GET";
        r.URI         = "/1.1/collections/list.json";

        r.queries.push_back({"cursor", cursor});

        if (p.screen_name.has_value())
            r.queries.push_back({"screen_name", p.screen_name.value()});

        if (p.user_id.has_value())
            r.queries.push_back({"user_id", to_string(p.user_id.value())});

        if (p.tweet_id.has_value())
            r.queries.push_back({"tweet_id", to_string(p.tweet_id.value())});

        if (p.count.has_value())
            r.queries.push_back({"count", to_string(p.count.value())});

        authorize(r, keys);

        auto const response = https_read(https_write(r));
        cursor              = to_ptree(response).get<std::string>(
            "response.cursors.next_cursor", "0");
        result.append(response);
    }
    return result;
}

auto get_collection_info(oauth::Credentials const& keys, std::string const& id)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/collections/show.json";

    r.queries.push_back({"id", id});

    authorize(r, keys);

    return https_read(https_write(r));
}

}  // namespace twitter
