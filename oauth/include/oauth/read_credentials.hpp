#ifndef OAUTH_READ_CREDENTIALS_HPP
#define OAUTH_READ_CREDENTIALS_HPP
#include <istream>
#include <string>

#include <oauth/credentials.hpp>

namespace oauth {

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

}  // namespace oauth
#endif  // OAUTH_READ_CREDENTIALS_HPP
