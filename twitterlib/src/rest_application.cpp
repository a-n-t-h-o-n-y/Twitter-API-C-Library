#include <twitterlib/rest/application.hpp>

#include <string>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>

namespace twitter {

auto get_application_rate_limit_status(std::string const& bearer_token)
    -> network::Response
{
    auto r          = network::Request{};
    r.HTTP_method   = "GET";
    r.URI           = "/1.1/application/rate_limit_status.json";
    r.authorization = "Bearer " + bearer_token;

    return https_read(https_write(r));
}

}  // namespace twitter
