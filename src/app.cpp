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
#include <iostream>

namespace tal {

Response App::send(Request& request, const Account& account) {
    // Inject OAuth to the request
    detail::authorize(request, *this, account);

    // Send request to generic send function
    Response response = detail::send_HTTP(request);
    return response;
}

Response App::send(Request& request) {
    // Inject Application only OAuth into the request
    detail::authorize(request, *this);

    // send request to generic send function
    return detail::send_HTTP(request);
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

void App::verify_credentials() {
    Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/account/verify_credentials.json";
    std::cout << this->send(r) << std::endl;
    // detail::digest(this->send(r));
}

void App::get_favorites(const std::string& user) {
    Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/favorites/list.json";
    r.add_query("screen_name", user);
    r.add_query("count", "1");
    std::cout << this->send(r) << std::endl;
}

}  // namespace tal
