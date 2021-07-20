#include <twitterlib/rest_api/rest_account.hpp>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/oauth/credentials.hpp>
#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <twitterlib/detail/to_string.hpp>

namespace twitter {

auto get_account_settings(network::Credentials const& keys) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.host        = "api.twitter.com";
    r.URI         = "/1.1/account/settings.json";

    network::authorize(r, keys);

    return https_read(https_write(r));
}

auto verify_credentials(network::Credentials const& keys,
                        bool include_entities,
                        bool skip_status,
                        bool include_email) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/account/verify_credentials.json";

    r.queries.push_back(
        {"include_entities", detail::to_string(include_entities)});
    r.queries.push_back({"skip_status", detail::to_string(skip_status)});
    r.queries.push_back({"include_email", detail::to_string(include_email)});

    network::authorize(r, keys);

    return https_read(https_write(r));
}

}  // namespace twitter
