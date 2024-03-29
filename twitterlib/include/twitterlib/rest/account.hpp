#ifndef TWITTERLIB_REST_ACCOUNT_HPP
#define TWITTERLIB_REST_ACCOUNT_HPP
#include <cstdint>
#include <optional>
#include <string>

#include <networklib/response.hpp>
#include <oauth/credentials.hpp>

#include <twitterlib/detail/types.hpp>
#include <twitterlib/objects/user.hpp>

namespace twitter {

/// Get the \p keys Account's Settings as JSON.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/get-account-settings */
[[nodiscard]] auto get_account_settings(oauth::Credentials const& keys)
    -> network::Response;

struct Verify_credentials_parameters {
    std::optional<bool> include_entities = std::nullopt;
    std::optional<bool> skip_status      = std::nullopt;
    std::optional<bool> include_email    = std::nullopt;
};

/// Return User details who owns \p keys, throws 401 HTTP error if can't verify.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/get-account-verify_credentials */
[[nodiscard]] auto verify_credentials_JSON(
    oauth::Credentials const& keys,
    Verify_credentials_parameters const& p = {}) -> network::Response;

/// Return the User who owns \p keys, throws 401 HTTP error if can't verify.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/get-account-verify_credentials */
[[nodiscard]] auto verify_credentials(
    oauth::Credentials const& keys,
    Verify_credentials_parameters const& p = {}) -> User;

struct Get_profile_banner_parameters {
    std::optional<std::string> screen_name;
    std::optional<std::int64_t> user_id = std::nullopt;
};

/// Return JSON info about profile banner of authenticated user.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/get-users-profile_banner
 *  Must provide either screen_name, user_id, or both to disambiguate. */
[[nodiscard]] auto get_profile_banner(oauth::Credentials const& keys,
                                      Get_profile_banner_parameters const& p)
    -> network::Response;

/// Return the authenticated user's saved search queries.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/get-saved_searches-list */
[[nodiscard]] auto get_saved_searches(oauth::Credentials const& keys)
    -> network::Response;

/// Return info about the saved search with \p searh_id from authenticated user.
[[nodiscard]] auto get_saved_search_info(oauth::Credentials const& keys,
                                         std::int64_t search_id)
    -> network::Response;

/// Remove the authenticated user's profile banner image.
/** Throws std::runtime_error on failure.
 *  https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-remove_profile_banner
 */
void remove_profile_banner(oauth::Credentials const& keys);

struct Account_settings {
    std::optional<Sleep_time> sleep_time             = std::nullopt;
    std::optional<Hour> start_sleep_time             = std::nullopt;
    std::optional<Hour> end_sleep_time               = std::nullopt;
    std::optional<std::string> time_zone             = std::nullopt;
    std::optional<std::int64_t> trend_location_woeid = std::nullopt;
    std::optional<std::string> lang                  = std::nullopt;
};

/// Update the authenticated user's settings.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-settings */
void update_account(oauth::Credentials const& keys,
                    Account_settings const& p = {});

struct Profile_settings {
    std::optional<std::string> name             = std::nullopt;
    std::optional<std::string> url              = std::nullopt;
    std::optional<std::string> location         = std::nullopt;
    std::optional<std::string> description      = std::nullopt;
    std::optional<Hex_color> profile_link_color = std::nullopt;
    std::optional<bool> include_entities        = std::nullopt;
    std::optional<bool> skip_status             = std::nullopt;
};

/// Update certain account profile settings.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-update_profile */
auto update_profile(oauth::Credentials const& keys,
                    Profile_settings const& p = {}) -> network::Response;

struct Profile_banner_bytes {
    std::vector<unsigned char> image;
    std::optional<int> width       = std::nullopt;
    std::optional<int> height      = std::nullopt;
    std::optional<int> offset_left = std::nullopt;
    std::optional<int> offset_top  = std::nullopt;
};

/// Update the authenticated user's profile banner image using raw image bytes.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-update_profile_banner */
void update_profile_banner(oauth::Credentials const& keys,
                           Profile_banner_bytes const& p);

struct Profile_banner_base64 {
    std::string image;
    std::optional<int> width       = std::nullopt;
    std::optional<int> height      = std::nullopt;
    std::optional<int> offset_left = std::nullopt;
    std::optional<int> offset_top  = std::nullopt;
};

/// Update the authenticated user's profile banner image using base64 encoding.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-update_profile_banner */
void update_profile_banner(oauth::Credentials const& keys,
                           Profile_banner_base64 const& p);

struct Profile_image_bytes {
    std::vector<unsigned char> image;
    std::optional<bool> include_entities = std::nullopt;
    std::optional<bool> skip_status      = std::nullopt;
};

/// Update the authenticated user's profile image using raw image bytes.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-update_profile_image */
auto update_profile_image(oauth::Credentials const& keys,
                          Profile_image_bytes const& p) -> network::Response;

struct Profile_image_base64 {
    std::string image;
    std::optional<bool> include_entities = std::nullopt;
    std::optional<bool> skip_status      = std::nullopt;
};

/// Update the authenticated user's profile image using base64 encoding.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-account-update_profile_image */
auto update_profile_image(oauth::Credentials const& keys,
                          Profile_image_base64 const& p) -> network::Response;

/// Create a new saved search for the authenticated user.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-saved_searches-create */
[[nodiscard]] auto create_saved_search(oauth::Credentials const& keys,
                                       std::string const& query)
    -> network::Response;

/// Destroy an existing saved search of the authenticated user.
/** https://developer.twitter.com/en/docs/twitter-api/v1/accounts-and-users/manage-account-settings/api-reference/post-saved_searches-destroy-id */
auto destroy_saved_search(oauth::Credentials const& keys, std::int64_t id)
    -> network::Response;

}  // namespace twitter
#endif  // TWITTERLIB_REST_ACCOUNT_HPP
