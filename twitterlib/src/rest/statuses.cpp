#include <twitterlib/rest/statuses.hpp>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <networklib/response.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>
#include <twitterlib/detail/utility.hpp>

namespace twitter {

auto update_status(oauth::Credentials const& keys,
                   Update_status_parameters const& p) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/statuses/update.json";

    r.queries.push_back({"status", p.message});

    if (p.in_reply_to_status_id.has_value()) {
        r.queries.push_back({"in_reply_to_status_id",
                             to_string(p.in_reply_to_status_id.value())});
    }
    if (p.auto_populate_reply_metadata.has_value()) {
        r.queries.push_back(
            {"auto_populate_reply_metadata",
             to_string(p.auto_populate_reply_metadata.value())});
    }
    if (!p.exclude_reply_user_ids.empty()) {
        r.queries.push_back(
            {"exclude_reply_user_ids", to_string(p.exclude_reply_user_ids)});
    }
    if (p.attachment_url.has_value()) {
        r.queries.push_back({"attachment_url", p.attachment_url.value()});
    }
    if (!p.media_ids.empty()) {
        r.queries.push_back({"media_ids", to_string(p.media_ids)});
    }
    if (p.possibly_sensitive.has_value()) {
        r.queries.push_back(
            {"possibly_sensitive", to_string(p.possibly_sensitive.value())});
    }
    if (p.lat_and_long.has_value()) {
        r.queries.push_back(
            {"lat", to_string(p.lat_and_long.value().latitude)});
        r.queries.push_back(
            {"long", to_string(p.lat_and_long.value().longitude)});
    }
    if (p.place_id.has_value()) {
        r.queries.push_back({"place_id", p.place_id.value()});
    }
    if (p.display_coordinates.has_value()) {
        r.queries.push_back(
            {"display_coordinates", to_string(p.display_coordinates.value())});
    }
    if (p.trim_user.has_value()) {
        r.queries.push_back({"trim_user", to_string(p.trim_user.value())});
    }
    if (p.enable_dmcommands.has_value()) {
        r.queries.push_back(
            {"enable_dmcommands", to_string(p.enable_dmcommands.value())});
    }
    if (p.fail_dmcommands.has_value()) {
        r.queries.push_back(
            {"fail_dmcommands", to_string(p.fail_dmcommands.value())});
    }
    if (p.card_uri.has_value()) {
        r.queries.push_back({"card_uri", p.card_uri.value()});
    }

    authorize(r, keys);

    return https_read(https_write(r));
}

}  // namespace twitter
