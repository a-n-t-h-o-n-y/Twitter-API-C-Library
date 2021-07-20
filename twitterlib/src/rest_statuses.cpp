#include <twitterlib/rest_api/rest_statuses.hpp>

#include <string>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/oauth/credentials.hpp>
#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>

namespace twitter {

void update_status(network::Credentials const& keys, std::string const& message)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/statuses/update.json";
    r.messages.push_back({"status", message});

    network::authorize(r, keys);

    // TODO read response and throw if error?
    (void)https_read(https_write(r));
}

}  // namespace twitter
