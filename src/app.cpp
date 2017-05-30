#include "app.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>  // temp
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "message.hpp"
#include "detail/network.hpp"
#include "request.hpp"
#include "detail/oauth.hpp"
#include "detail/encode.hpp"
#include "objects/user.hpp"
#include "objects/tweet.hpp"
#include "detail/to_string.hpp"

namespace tal {

Message App::send(Request& request, const Account& account) {
    // Inject OAuth to the request
    detail::authorize(request, *this, account);

    // Send request to generic send function
    return detail::send_HTTP(request, this->io_service());
}

Message App::send(Request& request) {
    // Inject Application only OAuth into the request
    detail::authorize(request, *this);

    // send request to generic send function
    return detail::send_HTTP(request, this->io_service());
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
    this->send(us_request, account_);
}

User App::verify_credentials(bool include_entities,
                             bool skip_status,
                             bool include_email) {
    Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/account/verify_credentials.json";

    r.add_query("include_entities", detail::to_string(include_entities));
    r.add_query("skip_status", detail::to_string(skip_status));
    r.add_query("include_email", detail::to_string(include_email));

    return User{this->send(r, account_)};
}

std::vector<Tweet> App::get_favorites(const std::string& screen_name,
                                      int count,
                                      bool include_entities,
                                      std::int64_t user_id,
                                      std::int64_t since_id,
                                      std::int64_t max_id) {
    Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/favorites/list.json";

    if (!screen_name.empty()) {
        r.add_query("screen_name", screen_name);
    }
    if (count != -1) {
        r.add_query("count", detail::to_string(count));
    }
    r.add_query("include_entities", detail::to_string(include_entities));
    if (user_id != -1) {
        r.add_query("user_id", detail::to_string(user_id));
    }
    if (since_id != -1) {
        r.add_query("since_id", detail::to_string(since_id));
    }
    if (since_id != -1) {
        r.add_query("max_id", detail::to_string(max_id));
    }

    // Parse Tweet Array
    boost::property_tree::ptree tree;
    std::stringstream json_stream{this->send(r).json()};
    boost::property_tree::read_json(json_stream, tree);
    tree = tree.get_child("");
    std::vector<Tweet> result;
    for (const auto& pair : tree) {
        result.push_back(Tweet(pair.second));
    }
    return result;
}

void App::register_to_user_stream(Stream::Callback callback,
                                  Stream::Condition condition) {
    user_stream_.register_function(std::move(callback), std::move(condition));
}

void App::register_to_filtered_stream(Stream::Callback callback,
                                      Stream::Condition condition) {
    filtered_stream_.register_function(std::move(callback),
                                       std::move(condition));
}

void App::register_to_sample_stream(Stream::Callback callback,
                                    Stream::Condition condition) {
    sample_stream_.register_function(std::move(callback), std::move(condition));
}

}  // namespace tal
