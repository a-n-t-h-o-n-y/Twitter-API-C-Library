#include <twitterlib/rest/account.hpp>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/detail/to_string.hpp>

namespace twitter {

auto get_account_settings(oauth::Credentials const& keys) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.host        = "api.twitter.com";
    r.URI         = "/1.1/account/settings.json";

    authorize(r, keys);

    return https_read(https_write(r));
}

auto verify_credentials(oauth::Credentials const& keys,
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

    authorize(r, keys);

    return https_read(https_write(r));
}

}  // namespace twitter
