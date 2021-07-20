#ifndef NETWORKLIB_OAUTH_READ_KEYS_HPP
#define NETWORKLIB_OAUTH_READ_KEYS_HPP
#include <istream>
#include <string>

#include <networklib/oauth/credentials.hpp>

namespace network {

/// Read in OAuth Keys and Tokens from a file.
/** Throws std::runtime_error if \p stream can't be read, or has bad contents.
 *  File Format(order matters):
 *      consumer_key *KEY*
 *      consumer_token *TOKEN*
 *      user_token *USERTOKEN*
 *      token_secret *TOKENSECRET*
 */
[[nodiscard]] auto read_credentials(std::istream& stream) -> Credentials;

/// Read in OAuth Keys and Tokens from a file.
/** Throws std::runtime_error if \p filename can't be read, or has bad contents.
 *  File Format(order matters):
 *      consumer_key *KEY*
 *      consumer_token *TOKEN*
 *      user_token *USERTOKEN*
 *      token_secret *TOKENSECRET*
 */
[[nodiscard]] auto read_credentials(std::string const& filename) -> Credentials;

}  // namespace network
#endif  // NETWORKLIB_OAUTH_READ_KEYS_HPP
