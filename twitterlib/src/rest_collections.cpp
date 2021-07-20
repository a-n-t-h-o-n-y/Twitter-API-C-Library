#include <twitterlib/rest_api/rest_collections.hpp>

#include <string>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/oauth/credentials.hpp>
#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <twitterlib/detail/to_string.hpp>

namespace twitter {

auto get_collection(network::Credentials const& keys,
                    std::string const& id,
                    int count,
                    int max_position,
                    int min_position) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/collections/entries.json";
    r.queries.push_back({"id", id});

    if (count != -1)
        r.queries.push_back({"count", detail::to_string(count)});

    if (max_position != -1)
        r.queries.push_back({"max_position", detail::to_string(max_position)});

    if (min_position != -1)
        r.queries.push_back({"min_position", detail::to_string(min_position)});

    network::authorize(r, keys);

    return https_read(https_write(r));
}

auto find_collections(network::Credentials const& keys,
                      std::string const& screen_name,
                      std::int64_t /* user_id */,
                      std::int64_t /* tweet_id */,
                      int /* count */) -> network::Response
{
    using namespace network;

    auto cursor = std::string{"-1"};
    // not actually cursored, you need a way to accumulate what you return
    // while (cursor != "0") {
    auto r        = Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/collections/list.json";
    r.queries.push_back({"cursor", cursor});
    r.queries.push_back({"screen_name", screen_name});

    authorize(r, keys);

    auto const result = https_read(https_write(r));
    cursor            = get(to_ptree(result), "response.cursors.next_cursor");
    // }
    return result;
}

auto get_collection_info(network::Credentials const& keys,
                         std::string const& id) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/collections/show.json";
    r.queries.push_back({"id", id});

    network::authorize(r, keys);
    return https_read(https_write(r));
}

}  // namespace twitter
