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

auto get_account_settings(oauth::Credentials const& keys) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.host        = "api.twitter.com";
    r.URI         = "/1.1/account/settings.json";

    authorize(r, keys);

    return https_read(https_write(r));
}

auto verify_credentials_JSON(oauth::Credentials const& keys,
                             Verify_credentials_parameters const& p)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/account/verify_credentials.json";

    if (p.include_entities.has_value()) {
        r.queries.push_back(
            {"include_entities", to_string(p.include_entities.value())});
    }
    if (p.skip_status.has_value()) {
        r.queries.push_back({"skip_status", to_string(p.skip_status.value())});
    }
    if (p.include_email.has_value()) {
        r.queries.push_back(
            {"include_email", to_string(p.include_email.value())});
    }

    authorize(r, keys);

    return https_read(https_write(r));
}

auto verify_credentials(oauth::Credentials const& keys,
                        Verify_credentials_parameters const& p) -> User
{
    return parse_user(network::to_ptree(verify_credentials_JSON(keys, p)));
}

auto get_profile_banner(oauth::Credentials const& keys,
                        Get_profile_banner_parameters const& p)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/users/profile_banner.json";

    if (!p.user_id.has_value() && !p.screen_name.has_value())
        throw std::invalid_argument{"get_profile_banner()"};

    if (p.user_id.has_value())
        r.queries.push_back({"user_id", to_string(p.user_id.value())});
    if (p.screen_name.has_value())
        r.queries.push_back({"screen_name", p.screen_name.value()});

    authorize(r, keys);

    return https_read(https_write(r));
}

auto get_saved_searches(oauth::Credentials const& keys) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "GET";
    r.URI         = "/1.1/saved_searches/list.json";

    authorize(r, keys);

    return https_read(https_write(r));
}

auto get_saved_search_info(oauth::Credentials const& keys,
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

void update_account(oauth::Credentials const& keys, Account_settings const& p)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/settings.json";

    if (p.sleep_time.has_value()) {
        r.queries.push_back(
            {"sleep_time_enabled", to_string(p.sleep_time.value())});
    }
    if (p.start_sleep_time.has_value()) {
        r.queries.push_back(
            {"sleep_time_enabled", to_string(p.start_sleep_time.value())});
    }
    if (p.end_sleep_time.has_value()) {
        r.queries.push_back(
            {"sleep_time_enabled", to_string(p.end_sleep_time.value())});
    }
    if (p.time_zone.has_value()) {
        r.queries.push_back({"time_zone", p.time_zone.value()});
    }
    if (p.trend_location_woeid.has_value()) {
        r.queries.push_back({"trend_location_woeid",
                             to_string(p.trend_location_woeid.value())});
    }
    if (p.lang.has_value()) {
        r.queries.push_back({"lang", p.lang.value()});
    }

    authorize(r, keys);

    (void)https_read(https_write(r));
}

auto update_profile(oauth::Credentials const& keys, Profile_settings const& p)
    -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/update_profile.json";

    if (p.name.has_value()) {
        r.queries.push_back({"name", p.name.value()});
    }
    if (p.url.has_value()) {
        r.queries.push_back({"url", p.url.value()});
    }
    if (p.location.has_value()) {
        r.queries.push_back({"location", p.location.value()});
    }
    if (p.description.has_value()) {
        r.queries.push_back({"description", p.description.value()});
    }
    if (p.profile_link_color.has_value()) {
        r.queries.push_back(
            {"profile_link_color", to_string(p.profile_link_color.value())});
    }
    if (p.include_entities.has_value()) {
        r.queries.push_back(
            {"include_entities", to_string(p.include_entities.value())});
    }
    if (p.skip_status.has_value()) {
        r.queries.push_back({"skip_status", to_string(p.skip_status.value())});
    }

    authorize(r, keys);

    return https_read(https_write(r));
}

void update_profile_banner(oauth::Credentials const& keys,
                           Profile_banner_bytes const& p)
{
    return update_profile_banner(
        keys, {network::detail::base64_encode(p.image), p.width, p.height,
               p.offset_left, p.offset_top});
}

void update_profile_banner(oauth::Credentials const& keys,
                           Profile_banner_base64 const& p)
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/update_profile_banner.json";

    r.queries.push_back({"banner", p.image});

    if (p.width.has_value())
        r.queries.push_back({"width", to_string(p.width.value())});
    if (p.height.has_value())
        r.queries.push_back({"height", to_string(p.height.value())});
    if (p.offset_left.has_value())
        r.queries.push_back({"offset_left", to_string(p.offset_left.value())});
    if (p.offset_top.has_value())
        r.queries.push_back({"offset_top", to_string(p.offset_top.value())});

    authorize(r, keys);

    (void)https_read(https_write(r));
}

auto update_profile_image(oauth::Credentials const& keys,
                          Profile_image_bytes const& p) -> network::Response
{
    return update_profile_image(keys, {network::detail::base64_encode(p.image),
                                       p.include_entities, p.skip_status});
}

auto update_profile_image(oauth::Credentials const& keys,
                          Profile_image_base64 const& p) -> network::Response
{
    auto r        = network::Request{};
    r.HTTP_method = "POST";
    r.URI         = "/1.1/account/update_profile_image.json";

    r.queries.push_back({"image", p.image});

    if (p.include_entities.has_value()) {
        r.queries.push_back(
            {"include_entities", to_string(p.include_entities.has_value())});
    }
    if (p.skip_status.has_value()) {
        r.queries.push_back(
            {"skip_status", to_string(p.skip_status.has_value())});
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
