#include <twitterlib/twitter_stream.hpp>

#include <networklib/oauth/oauth.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <networklib/wait.hpp>
#include <twitterlib/account.hpp>
#include <twitterlib/app.hpp>

namespace twitter {

Stream_parameters build_user_stream_parameters() {
    Stream_parameters user_params;
    user_params.host = "userstream.twitter.com";
    user_params.URI = "/1.1/user.json";
    user_params.method = "GET";
    return user_params;
}

Stream_parameters build_filtered_stream_parameters() {
    Stream_parameters filtered_params;
    filtered_params.host = "stream.twitter.com";
    filtered_params.URI = "/1.1/statuses/filter.json";
    filtered_params.method = "POST";
    return filtered_params;
}

Stream_parameters build_sample_stream_parameters() {
    Stream_parameters sample_params;
    sample_params.host = "stream.twitter.com";
    sample_params.URI = "/1.1/statuses/sample.json";
    sample_params.method = "GET";
    return sample_params;
}

Twitter_stream::Twitter_stream(const App* app, const Stream_parameters& params)
    : app_{app}, params_{params} {}

void Twitter_stream::register_function(Callback f1, Condition f2) {
    stream_.register_function(f1, f2);
}

void Twitter_stream::open() {
    network::Request new_request{this->build_request()};
    stream_.set_request(new_request);
    stream_.open();
}

void Twitter_stream::close() {
    stream_.close();
}

// builds request, sets stream_.request, stream_.reconnect();
void Twitter_stream::reconnect() {
    network::Request new_request{this->build_request()};
    stream_.set_request(new_request);
    stream_.reconnect();
}

Stream_parameters& Twitter_stream::parameters() {
    return params_;
}

const Stream_parameters& Twitter_stream::parameters() const {
    return params_;
}

void Twitter_stream::wait() {
    network::wait();
}

// Builds the complete, authorized Request
network::Request Twitter_stream::build_request() {
    network::Request r{parameters_to_request(params_)};
    const Account& account{app_->account()};
    network::authorize(r, app_->key(), app_->secret(), account.token,
                       account.secret);
    return r;
}

// Only builds the shared parameters.
network::Request Twitter_stream::parameters_to_request(
    const Stream_parameters& params) {
    network::Request r;
    r.host = params.host;
    r.URI = params.URI;
    r.HTTP_method = params.method;
    r.content_type = "application/json";

    if (!params.delimited.empty()) {
        r.add_query("delimited", params.delimited);
    }
    r.add_query("stall_warnings", params.stall_warnings ? "true" : "false");
    if (!params.track.empty()) {
        std::stringstream ss;
        std::string comma;
        for (auto& str : params.track) {
            ss << comma << str;
            comma = ",";
        }
        r.add_query("track", ss.str());
    }
    if (params.use_locations_) {
        std::stringstream ss;
        ss << params.locations.first.longitude << ',';
        ss << params.locations.first.latitude << ',';
        ss << params.locations.second.longitude << ',';
        ss << params.locations.second.latitude;
        r.add_query("locations", ss.str());
    }
    if (!params.follow.empty()) {
        std::stringstream ss;
        std::string comma;
        for (auto& id : params.follow) {
            ss << comma << id;
            comma = ",";
        }
        r.add_query("follow", ss.str());
    }

    // User Streams Only
    if (params.host.find("user") != std::string::npos) {
        insert_user_parameters(r, params);
    }
    return r;
}

void Twitter_stream::insert_user_parameters(network::Request& r,
                                            const Stream_parameters& params) {
    if (!params.with.empty()) {
        r.add_query("with", params.with);
    }
    if (!params.replies.empty()) {
        r.add_query("replies", params.replies);
    }
    r.add_query("stringify_friend_ids",
                params.stringify_friend_ids ? "true" : "false");
}

}  // namespace twitter
