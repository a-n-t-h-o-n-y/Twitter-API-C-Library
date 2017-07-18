#include "app.hpp"

#include "message.hpp"
#include "detail/network.hpp"
#include "request.hpp"
#include "detail/oauth.hpp"
#include "detail/encode.hpp"
#include "objects/user.hpp"
#include "objects/tweet.hpp"
#include "detail/to_string.hpp"

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>

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
    us_request.URI = "/1.1/statuses/update.json";
    us_request.add_message("status", message);
    this->send(us_request, account_);
}

Message App::verify_credentials(bool include_entities,
                                bool skip_status,
                                bool include_email) {
    Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/account/verify_credentials.json";

    r.add_query("include_entities", detail::to_string(include_entities));
    r.add_query("skip_status", detail::to_string(skip_status));
    r.add_query("include_email", detail::to_string(include_email));
    return this->send(r, account_);
}

Message App::get_application_rate_limit_status() {
    Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/application/rate_limit_status.json";
    return this->send(r);
}

Message App::get_account_settings() {
    Request r;
    r.HTTP_method = "GET";
    r.host = "api.twitter.com";
    r.URI = "/1.1/account/settings.json";
    return this->send(r, account_);
}

Message App::get_account_rate_limit_status() {
    Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/application/rate_limit_status.json";
    return this->send(r, account_);
}

// cursored results
std::vector<std::int64_t> App::get_blocked_ids() {
    std::vector<std::int64_t> result;
    std::string cursor{"-1"};
    while (cursor != "0") {
        Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/blocks/ids.json";
        r.add_query("cursor", cursor);
        Message page = this->send(r, account_);
        for (auto& id : page.ptree().get_child("ids")) {
            result.push_back(id.second.get_value<std::int64_t>());
        }
        cursor = page.get("next_cursor");
    }
    return result;
}

std::vector<User> App::get_blocked_users(bool include_entities,
                                         bool skip_status) {
    std::vector<User> result;
    std::string cursor{"-1"};
    while (cursor != "0") {
        Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/blocks/list.json";
        r.add_query("cursor", cursor);
        Message page = this->send(r, account_);
        for (auto& user : page.ptree().get_child("users")) {
            result.emplace_back(user.second);
        }
        cursor = page.get("next_cursor");
    }
    return result;
}

Message App::get_collection(const std::string& id,
                            int count,
                            int max_position,
                            int min_position) {
    Request r;
    r.HTTP_method = "GET";
    r.URI = "/1.1/collections/entries.json";
    r.add_query("id", id);
    if (count != -1) {
        r.add_query("count", detail::to_string(count));
    }
    if (max_position != -1) {
        r.add_query("max_position", detail::to_string(max_position));
    }
    if (min_position != -1) {
        r.add_query("min_position", detail::to_string(min_position));
    }
    return this->send(r, account_);
}

Message App::find_collections(const std::string& screen_name,
                              std::int64_t user_id,
                              std::int64_t tweet_id,
                              int count) {
    Message result;
    std::string cursor{"-1"};
    // not actually cursored, you need a way to accumulate what you return
    while (cursor != "0") {
        Request r;
        r.HTTP_method = "GET";
        r.URI = "/1.1/collections/list.json";
        r.add_query("cursor", cursor);
        r.add_query("screen_name", screen_name);
        result = this->send(r, account_);
        cursor = result.get("response.cursors.next_cursor");
    }
    return result;
}

std::vector<Tweet> App::get_favorites(const std::string& screen_name,
                                      int count,
                                      bool include_entities,
                                      std::int64_t user_id,
                                      std::int64_t since_id,
                                      std::int64_t max_id) {
    Request r;
    r.HTTP_method = "GET";
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
        result.emplace_back(pair.second);
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
