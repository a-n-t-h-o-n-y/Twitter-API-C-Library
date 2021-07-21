#include <twitterlib/rest/statuses.hpp>

#include <string>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>

namespace twitter {

void update_status(oauth::Credentials const& keys, std::string const& message)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/statuses/update.json";
    r.messages.push_back({"status", message});

    authorize(r, keys);

    // TODO read response and throw if error?
    (void)https_read(https_write(r));
}

}  // namespace twitter
