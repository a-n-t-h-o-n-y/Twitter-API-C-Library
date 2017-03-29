#include "detail/oauth.hpp"
#include "account.hpp"
#include "app.hpp"
#include "request.hpp"
#include "detail/encode.hpp"

#include <algorithm>
#include <ctime>
#include <cctype>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <boost/algorithm/string.hpp>

// Helper functions here (they will not be accessibly from outside).
namespace {
using namespace tal;

std::string gen_nonce() {
    std::vector<unsigned char> nonce(32, ' ');
    RAND_bytes(nonce.data(), nonce.size());
    std::string nonce_string = detail::base64_encode(nonce);
    // remove all non-alphanumerics
    nonce_string.erase(
        std::remove_if(std::begin(nonce_string), std::end(nonce_string),
                       [](char c) { return !std::isalnum(c); }),
        std::end(nonce_string));
    return nonce_string;
}

std::string gen_timestamp() {
    std::stringstream time_ss;
    time_ss << std::time(nullptr);
    return time_ss.str();
}

std::string hmac_sha1_signature(const std::string& key,
                                const std::string& message) {
    std::vector<unsigned char> key_buffer(std::begin(key), std::end(key));
    std::vector<unsigned char> message_buffer(std::begin(message),
                                              std::end(message));
    unsigned int length = 20;
    std::vector<unsigned char> result_buffer(length, ' ');

    HMAC_CTX context;
    HMAC_CTX_init(&context);

    // Key
    HMAC_Init_ex(&context, static_cast<const void*>(key_buffer.data()),
                 key.length(), EVP_sha1(), nullptr);
    // Message
    HMAC_Update(&context, message_buffer.data(), message.length());
    // Resultant Signature
    HMAC_Final(&context, result_buffer.data(), &length);
    HMAC_CTX_cleanup(&context);

    return detail::base64_encode(result_buffer);
}

std::string gen_signature(const Request& request,
                          const App& app,
                          const Account& account,
                          const std::string& version,
                          const std::string& sig_method,
                          const std::string& nonce,
                          const std::string& timestamp) {
    const std::string base_url{request.HTTP_protocol + "://" + request.host +
                               request.URI};
    std::vector<std::string> encoded_parameters;
    // QueryString Parameters
    for (const auto& key_value : request.queries) {
        std::stringstream parameter_ss;
        parameter_ss << detail::url_encode(key_value.first) << '='
                     << detail::url_encode(key_value.second);
        encoded_parameters.push_back(parameter_ss.str());
    }
    // OAuth Parameters
    std::stringstream parameter_ss;
    parameter_ss << detail::url_encode("oauth_consumer_key") << '='
                 << detail::url_encode(app.key());
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << detail::url_encode("oauth_nonce") << '='
                 << detail::url_encode(nonce);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << detail::url_encode("oauth_signature_method") << '='
                 << detail::url_encode(sig_method);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << detail::url_encode("oauth_timestamp") << '='
                 << detail::url_encode(timestamp);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << detail::url_encode("oauth_token") << '='
                 << detail::url_encode(account.token());
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    parameter_ss << detail::url_encode("oauth_version") << '='
                 << detail::url_encode(version);
    encoded_parameters.push_back(parameter_ss.str());
    parameter_ss.str(std::string());

    // Message Body Parameters
    for (const auto& key_value : request.message_body) {
        std::stringstream parameter_ss;
        parameter_ss << detail::url_encode(key_value.first) << '='
                     << detail::url_encode(key_value.second);
        encoded_parameters.push_back(parameter_ss.str());
    }

    // Build parameters string.
    std::sort(std::begin(encoded_parameters), std::end(encoded_parameters));
    std::stringstream parameters_ss;
    std::string seperator{""};
    for (const auto& key_value : encoded_parameters) {
        parameters_ss << seperator << key_value;
        seperator = "&";
    }
    std::string parameters_string{parameters_ss.str()};

    std::stringstream sig_base_ss;
    sig_base_ss << boost::to_upper_copy(request.HTTP_method) << '&';
    sig_base_ss << detail::url_encode(base_url) << '&';
    sig_base_ss << detail::url_encode(parameters_string);
    const std::string sig_base_string{sig_base_ss.str()};

    const std::string signing_key{detail::url_encode(app.secret()) + '&' +
                                  detail::url_encode(account.secret())};
    return hmac_sha1_signature(signing_key, sig_base_string);
}

// Inserts the constructed oauth header into the original request
void integrate_oauth(Request& original, const std::string& oauth_header) {
    original.authorization = oauth_header;
}

}  // namespace

namespace tal {
namespace detail {

void authorize(Request& request, const App& app, const Account& account) {
    const std::string consumer_key = app.key();
    const std::string consumer_secret = app.secret();
    const std::string token = account.token();
    const std::string token_secret = account.secret();
    const std::string version = "1.0";
    const std::string sig_method = "HMAC-SHA1";
    const std::string nonce = gen_nonce();
    const std::string timestamp = gen_timestamp();
    const std::string signature = gen_signature(request, app, account, version,
                                                sig_method, nonce, timestamp);

    // Build OAuth string from parameters.
    std::stringstream oauth;
    oauth << "OAuth ";
    oauth << url_encode("oauth_consumer_key") << "=\""
          << url_encode(consumer_key) << "\", ";
    oauth << url_encode("oauth_nonce") << "=\"" << url_encode(nonce) << "\", ";
    oauth << url_encode("oauth_signature") << "=\"" << url_encode(signature)
          << "\", ";
    oauth << url_encode("oauth_signature_method") << "=\""
          << url_encode(sig_method) << "\", ";
    oauth << url_encode("oauth_timestamp") << "=\"" << url_encode(timestamp)
          << "\", ";
    oauth << url_encode("oauth_token") << "=\"" << url_encode(token) << "\", ";
    oauth << url_encode("oauth_version") << "=\"" << url_encode(version)
          << '\"';

    integrate_oauth(request, oauth.str());
}

/// Add App OAuth 1.0a header to HTTP request.
void authorize(Request& request, App& app) {
    if (app.bearer_token().empty()) {
        app.acquire_bearer_token();
    }
    std::string oauth{"Bearer " + app.bearer_token()};
    integrate_oauth(request, oauth);
}

}  // namespace detail
}  // namespace tal
