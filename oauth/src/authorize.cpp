#include <oauth/authorize.hpp>

#include <algorithm>
#include <cctype>
#include <ctime>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <openssl/hmac.h>
#include <openssl/rand.h>

#include <boost/algorithm/string.hpp>

#include <networklib/detail/encode.hpp>
#include <networklib/request.hpp>

using network::detail::url_encode;

namespace {

[[nodiscard]] auto gen_nonce() -> std::string
{
    auto nonce = std::vector<unsigned char>(32, ' ');
    RAND_bytes(nonce.data(), nonce.size());
    auto nonce_string = network::detail::base64_encode(nonce);
    // remove all non-alphanumerics
    nonce_string.erase(
        std::remove_if(std::begin(nonce_string), std::end(nonce_string),
                       [](char c) { return !std::isalnum(c); }),
        std::end(nonce_string));
    return nonce_string;
}

[[nodiscard]] auto gen_timestamp() -> std::string
{
    auto time_ss = std::stringstream{};
    time_ss << std::time(nullptr);
    return time_ss.str();
}

[[nodiscard]] auto hmac_sha1_signature(std::string_view key,
                                       std::string_view message) -> std::string
{
    auto const key_buffer =
        std::vector<unsigned char>(std::cbegin(key), std::cend(key));
    auto const message_buffer =
        std::vector<unsigned char>(std::cbegin(message), std::cend(message));

    auto length        = 20u;
    auto result_buffer = std::vector<unsigned char>(length, ' ');

    HMAC_CTX* context = HMAC_CTX_new();
    HMAC_CTX_reset(context);

    // Key
    HMAC_Init_ex(context, static_cast<const void*>(key_buffer.data()),
                 key.size(), EVP_sha1(), nullptr);
    // Message
    HMAC_Update(context, message_buffer.data(), message.size());

    // Resultant Signature
    HMAC_Final(context, result_buffer.data(), &length);

    return network::detail::base64_encode(result_buffer);
}

[[nodiscard]] auto gen_signature(network::Request const& request,
                                 oauth::Credentials keys,
                                 std::string_view version,
                                 std::string_view sig_method,
                                 std::string_view nonce,
                                 std::string_view timestamp) -> std::string
{
    auto const base_url = std::string{request.HTTP_protocol}
                              .append("://")
                              .append(request.host)
                              .append(request.URI);
    auto encoded_parameters = std::vector<std::string>{};
    // QueryString Parameters
    for (auto const& [key, value] : request.queries) {
        encoded_parameters.push_back(url_encode(key) + '=' + url_encode(value));
    }

    // OAuth Parameters
    encoded_parameters.push_back(url_encode("oauth_consumer_key")
                                     .append(1, '=')
                                     .append(url_encode(keys.consumer_key)));

    encoded_parameters.push_back(
        url_encode("oauth_nonce").append(1, '=').append(url_encode(nonce)));

    encoded_parameters.push_back(url_encode("oauth_signature_method")
                                     .append(1, '=')
                                     .append(url_encode(sig_method)));

    encoded_parameters.push_back(url_encode("oauth_timestamp")
                                     .append(1, '=')
                                     .append(url_encode(timestamp)));

    encoded_parameters.push_back(url_encode("oauth_token")
                                     .append(1, '=')
                                     .append(url_encode(keys.user_token)));

    encoded_parameters.push_back(
        url_encode("oauth_version").append(1, '=').append(url_encode(version)));

    // Message Body Parameters
    for (auto const& [key, value] : request.messages) {
        encoded_parameters.push_back(
            url_encode(key).append(1, '=').append(url_encode(value)));
    }

    // Build parameters string.
    std::sort(std::begin(encoded_parameters), std::end(encoded_parameters));
    auto separator         = std::string{};
    auto parameters_string = std::string{};
    for (auto& key_value_str : encoded_parameters) {
        parameters_string.append(separator).append(std::move(key_value_str));
        separator = "&";
    }

    auto sig_base_string =
        boost::to_upper_copy(request.HTTP_method)
            .append(1, '&')
            .append(url_encode(base_url).append(1, '&').append(
                url_encode(parameters_string)));

    auto signing_key = url_encode(keys.consumer_secret)
                           .append(1, '&')
                           .append(url_encode(keys.token_secret));

    return hmac_sha1_signature(std::move(signing_key),
                               std::move(sig_base_string));
}

}  // namespace

namespace oauth {

/// Add App OAuth 1.0a header to HTTP request.
void authorize(network::Request& request, Credentials const& keys)
{
    constexpr auto version    = "1.0";
    constexpr auto sig_method = "HMAC-SHA1";
    auto const nonce          = gen_nonce();
    auto const timestamp      = gen_timestamp();
    auto const signature =
        gen_signature(request, keys, version, sig_method, nonce, timestamp);

    // Build OAuth string from parameters.
    auto oauth = std::ostringstream{};
    oauth << "OAuth ";
    oauth << url_encode("oauth_consumer_key") << "=\""
          << url_encode(keys.consumer_key) << "\", ";
    oauth << url_encode("oauth_nonce") << "=\"" << url_encode(nonce) << "\", ";
    oauth << url_encode("oauth_signature") << "=\"" << url_encode(signature)
          << "\", ";
    oauth << url_encode("oauth_signature_method") << "=\""
          << url_encode(sig_method) << "\", ";
    oauth << url_encode("oauth_timestamp") << "=\"" << url_encode(timestamp)
          << "\", ";
    oauth << url_encode("oauth_token") << "=\"" << url_encode(keys.user_token)
          << "\", ";
    oauth << url_encode("oauth_version") << "=\"" << url_encode(version)
          << '\"';

    request.authorization = oauth.str();
}

}  // namespace oauth
