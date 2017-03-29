#include "app.hpp"

#include "detail/network.hpp"
#include "request.hpp"
#include "response.hpp"
#include "detail/oauth.hpp"
#include "detail/encode.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include <cstddef>

#include <iostream>  // temp

namespace tal {

Response App::send(const Request& request, const Account& account) {
    // Inject OAuth to the request
    Request authenticated_request = detail::authorize(request, *this, account);
    // std::cout << authenticated_request;
    // std::cout << std::endl;

    // Send request to generic send function
    Response response = detail::send_HTTP(authenticated_request);
    // std::cout << response;
    return response;
}

Response App::send(const Request& request) {
    // Inject Application only OAuth into the request
    Request authenticated_request = detail::authorize(request, *this);

    // send request to generic send function
    Response response = detail::send_HTTP(authenticated_request);
    // std::cout << response;
    return response;  // combine this with above detail::send once cout gone.
}

void App::set_account(const Account& account) {
    account_ = account;
}

void App::update_status(const std::string& message) {
    Request us_request;
    us_request.HTTP_method = "POST";
    us_request.host = "api.twitter.com";
    us_request.URI = "/1.1/statuses/update.json";

    us_request.add_message("status", message);

    detail::digest(this->send(us_request, account_));
    std::cout << "Tweet sent: " << message;
}

// void App::acquire_bearer_token() {
//     std::string token_credentials = detail::url_encode(this->key()) + ':' +
//                                     detail::url_encode(this->secret());
//     std::vector<unsigned char> token_base64(std::begin(token_credentials),
//                                             std::end(token_credentials));
//     token_credentials = detail::base64_encode(token_base64);
//     Request bearer_request;
//     bearer_request.HTTP_method = "POST";
//     bearer_request.URI = "/oauth2/token";
//     bearer_request.authorization = "Basic " + token_credentials;
//     bearer_request.content_type += ";charset=UTF8";
//     bearer_request.add_message("grant_type", "client_credentials");
//     bearer_request.add_query("include_entities", "true");
//     bearer_request.add_header("Accept-Encoding", "gzip");

//     Response response = detail::send_HTTP(bearer_request);
//     // Makes sure the response was OK.
//     detail::digest(response);
//     // std::cout << bearer_request;
//     std::cout << response;

//     // Parse response for bearer token and save it in bearer_token_

//     // std::string token_type = response.message_body.substr(
//     //     response.message_body.find("token_type") + 12, 6);
//     // if (token_type != "bearer") {
//     //     throw std::runtime_error(
//     //         "Wrong token type when attempting to aquire bearer token.");
//     // }
//     // std::size_t token_beg = response.message_body.find("access_token") +
//     15;
//     // std::size_t token_end = response.message_body.find("\"}");
//     // this->bearer_token_ =
//     //     response.message_body.substr(token_beg, token_end - token_beg);
// }

// void App::contact_google() {
//     Request request;
//     request.host = "www.google.com";
//     request.URI = "/";
//     request.HTTP_method = "GET";

//     Response response = detail::send_HTTP(request);
//     std::cout << response.message_body;
// }

}  // namespace tal
