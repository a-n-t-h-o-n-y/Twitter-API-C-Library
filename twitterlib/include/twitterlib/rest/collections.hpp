#ifndef TWITTERLIB_REST_COLLECTIONS_HPP
#define TWITTERLIB_REST_COLLECTIONS_HPP
#include <cstdint>
#include <optional>
#include <string>

#include <networklib/response.hpp>
#include <oauth/credentials.hpp>

namespace twitter {

struct Get_collection_parameters {
    std::string id;
    std::optional<int> count        = std::nullopt;
    std::optional<int> max_position = std::nullopt;
    std::optional<int> min_position = std::nullopt;
};

/// Return a collection of tweets given by \p id.
/** https://developer.twitter.com/en/docs/twitter-api/v1/tweets/curate-a-collection/api-reference/get-collections-entries */
[[nodiscard]] auto get_collection(oauth::Credentials const& keys,
                                  Get_collection_parameters const& p)
    -> network::Response;

struct Find_collections_parameters {
    std::optional<std::string> screen_name = std::nullopt;
    std::optional<std::int64_t> user_id    = std::nullopt;
    std::optional<std::int64_t> tweet_id   = std::nullopt;
    std::optional<int> count               = std::nullopt;
};

/// Retrieve info on collections of a given user.
/** https://developer.twitter.com/en/docs/twitter-api/v1/tweets/curate-a-collection/api-reference/get-collections-list */
[[nodiscard]] auto find_collections(oauth::Credentials const& keys,
                                    Find_collections_parameters const& p)
    -> network::Response;

/// Return infomation about a specific collection.
/** https://developer.twitter.com/en/docs/twitter-api/v1/tweets/curate-a-collection/api-reference/get-collections-show */
[[nodiscard]] auto get_collection_info(oauth::Credentials const& keys,
                                       std::string const& id)
    -> network::Response;

// POST collections/create
// POST collections/destroy
// POST collections/entries/add
// POST collections/entries/curate
// POST collections/entries/move
// POST collections/entries/remove
// POST collections/update

}  // namespace twitter
#endif  // TWITTERLIB_REST_COLLECTIONS_HPP
