#include <oauth/bearer_token.hpp>

#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <networklib/detail/encode.hpp>
#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>

using network::detail::url_encode;

namespace oauth {

auto get_bearer_token(std::string_view consumer_key,
                      std::string_view consumer_secret) -> std::string
{
    auto token_credentials = url_encode(consumer_key)
                                 .append(1, ':')
                                 .append(url_encode(consumer_secret));
    auto const token_base64 = std::vector<unsigned char>(
        std::cbegin(token_credentials), std::cend(token_credentials));
    token_credentials = network::detail::base64_encode(token_base64);

    auto bearer_request          = network::Request{};
    bearer_request.HTTP_method   = "POST";
    bearer_request.URI           = "/oauth2/token";
    bearer_request.authorization = "Basic " + token_credentials;
    bearer_request.content_type += ";charset=UTF-8";
    bearer_request.messages.push_back({"grant_type", "client_credentials"});
    bearer_request.queries.push_back({"include_entities", "true"});
    bearer_request.headers.push_back({"Accept-Encoding", "gzip"});

    auto const message =
        network::to_ptree(https_read(https_write(bearer_request)));
    auto const token_type = network::get(message, "token_type");
    if (token_type != "bearer")
        throw std::runtime_error("Invalid bearer token type");

    // app.set_bearer_token(get(message, "access_token"));

    return network::get(message, "access_token");
}

}  // namespace oauth
