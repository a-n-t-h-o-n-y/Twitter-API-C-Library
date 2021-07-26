#include <twitterlib/rest/account.hpp>

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>

#include <networklib/detail/encode.hpp>
#include <networklib/https_read.hpp>
#include <networklib/https_write.hpp>
#include <networklib/request.hpp>
#include <oauth/authorize.hpp>
#include <oauth/credentials.hpp>

#include <twitterlib/detail/types.hpp>
#include <twitterlib/detail/utility.hpp>

namespace twitter {

auto get_account_settings_JSON(oauth::Credentials const& keys)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.host        = "api.twitter.com";
    r.URI         = "/1.1/account/settings.json";

    authorize(r, keys);

    return https_read(https_write(r));
}

auto verify_credentials_JSON(oauth::Credentials const& keys,
                             bool include_entities,
                             bool skip_status,
                             bool include_email) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/account/verify_credentials.json";

    r.queries.push_back({"include_entities", to_string(include_entities)});
    r.queries.push_back({"skip_status", to_string(skip_status)});
    r.queries.push_back({"include_email", to_string(include_email)});

    authorize(r, keys);

    return https_read(https_write(r));
}

auto verify_credentials(oauth::Credentials const& keys,
                        bool include_entities,
                        bool skip_status,
                        bool include_email) -> User
{
    return parse_user(network::to_ptree(verify_credentials_JSON(
        keys, include_entities, skip_status, include_email)));
}

auto get_profile_banner_JSON(oauth::Credentials const& keys,
                             std::optional<std::string> screen_name,
                             std::optional<std::int64_t> user_id)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/users/profile_banner.json";

    if (!user_id.has_value() && !screen_name.has_value())
        throw std::invalid_argument{"get_profile_banner_JSON()"};

    if (user_id.has_value())
        r.queries.push_back({"user_id", to_string(user_id.value())});
    if (screen_name.has_value())
        r.queries.push_back({"screen_name", screen_name.value()});

    authorize(r, keys);

    return https_read(https_write(r));
}

auto get_saved_searches_JSON(oauth::Credentials const& keys)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/saved_searches/list.json";

    authorize(r, keys);

    return https_read(https_write(r));
}

auto get_saved_search_info_JSON(oauth::Credentials const& keys,
                                std::int64_t search_id) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI = "/1.1/saved_searches/show/" + to_string(search_id) + ".json";

    authorize(r, keys);

    return https_read(https_write(r));
}

void remove_profile_banner(oauth::Credentials const& keys)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/remove_profile_banner.json";

    authorize(r, keys);

    (void)https_read(https_write(r));
}

void update_account_settings(oauth::Credentials const& keys,
                             std::optional<Sleep_time> sleep_time,
                             std::optional<Hour> start_sleep_time,
                             std::optional<Hour> end_sleep_time,
                             std::optional<std::string> time_zone,
                             std::optional<std::int64_t> trend_location_woeid,
                             std::optional<std::string> lang)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/settings.json";

    if (sleep_time.has_value()) {
        r.queries.push_back(
            {"sleep_time_enabled", to_string(sleep_time.value())});
    }
    if (start_sleep_time.has_value()) {
        r.queries.push_back(
            {"sleep_time_enabled", to_string(start_sleep_time.value())});
    }
    if (end_sleep_time.has_value()) {
        r.queries.push_back(
            {"sleep_time_enabled", to_string(end_sleep_time.value())});
    }
    if (time_zone.has_value()) {
        r.queries.push_back({"time_zone", time_zone.value()});
    }
    if (trend_location_woeid.has_value()) {
        r.queries.push_back(
            {"trend_location_woeid", to_string(trend_location_woeid.value())});
    }
    if (lang.has_value()) {
        r.queries.push_back({"lang", lang.value()});
    }

    authorize(r, keys);

    (void)https_read(https_write(r));
}

auto update_profile(oauth::Credentials const& keys,
                    std::optional<std::string> name,
                    std::optional<std::string> url,
                    std::optional<std::string> location,
                    std::optional<std::string> description,
                    std::optional<Hex_color> profile_link_color,
                    std::optional<bool> include_entities,
                    std::optional<bool> skip_status) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/update_profile.json";

    if (name.has_value()) {
        r.queries.push_back({"name", name.value()});
    }
    if (url.has_value()) {
        r.queries.push_back({"url", url.value()});
    }
    if (location.has_value()) {
        r.queries.push_back({"location", location.value()});
    }
    if (description.has_value()) {
        r.queries.push_back({"description", description.value()});
    }
    if (profile_link_color.has_value()) {
        r.queries.push_back(
            {"profile_link_color", to_string(profile_link_color.value())});
    }
    if (include_entities.has_value()) {
        r.queries.push_back(
            {"include_entities", to_string(include_entities.value())});
    }
    if (skip_status.has_value()) {
        r.queries.push_back({"skip_status", to_string(skip_status.value())});
    }

    authorize(r, keys);

    return https_read(https_write(r));
}

void update_profile_banner(oauth::Credentials const& keys,
                           std::vector<unsigned char> const& image_bytes,
                           std::optional<int> const width,
                           std::optional<int> const height,
                           std::optional<int> const offset_left,
                           std::optional<int> const offset_top)
{
    return update_profile_banner(keys,
                                 network::detail::base64_encode(image_bytes),
                                 width, height, offset_left, offset_top);
}

void update_profile_banner(oauth::Credentials const& keys,
                           std::string const& image_base64,
                           std::optional<int> const width,
                           std::optional<int> const height,
                           std::optional<int> const offset_left,
                           std::optional<int> const offset_top)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/update_profile_banner.json";

    r.queries.push_back({"banner", image_base64});

    if (width.has_value())
        r.queries.push_back({"width", to_string(width.value())});
    if (height.has_value())
        r.queries.push_back({"height", to_string(height.value())});
    if (offset_left.has_value())
        r.queries.push_back({"offset_left", to_string(offset_left.value())});
    if (offset_top.has_value())
        r.queries.push_back({"offset_top", to_string(offset_top.value())});

    authorize(r, keys);

    (void)https_read(https_write(r));
}

auto update_profile_image(oauth::Credentials const& keys,
                          std::vector<unsigned char> const& image_bytes,
                          std::optional<bool> include_entities,
                          std::optional<bool> skip_status) -> network::Response
{
    return update_profile_image(keys,
                                network::detail::base64_encode(image_bytes),
                                include_entities, skip_status);
}

auto update_profile_image(oauth::Credentials const& keys,
                          std::string const& image_base64,
                          std::optional<bool> include_entities,
                          std::optional<bool> skip_status) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/update_profile_image.json";

    r.queries.push_back({"image", image_base64});

    if (include_entities.has_value()) {
        r.queries.push_back(
            {"include_entities", to_string(include_entities.has_value())});
    }
    if (skip_status.has_value()) {
        r.queries.push_back(
            {"skip_status", to_string(skip_status.has_value())});
    }

    authorize(r, keys);

    return https_read(https_write(r));
}

auto create_saved_search(oauth::Credentials const& keys,
                         std::string const& query) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/saved_searches/create.json";

    r.queries.push_back({"query", query});

    authorize(r, keys);

    return https_read(https_write(r));
}

auto destroy_saved_search(oauth::Credentials const& keys, std::int64_t id)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/saved_searches/destroy/" + to_string(id) + ".json";

    authorize(r, keys);

    return https_read(https_write(r));
}

}  // namespace twitter
