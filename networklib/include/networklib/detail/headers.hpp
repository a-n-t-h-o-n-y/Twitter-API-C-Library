#ifndef NETWORKLIB_DETAIL_HEADERS_HPP
#define NETWORKLIB_DETAIL_HEADERS_HPP
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <networklib/detail/socket_stream.hpp>
#include <networklib/socket.hpp>

namespace network::detail {

struct Header {
    std::string key;
    std::string value;
};

using Headers = std::vector<Header>;

/// Retrieve the value associated with \p key in \p headers.
/** Returns empty string if \p key is not found in \p headers. */
[[nodiscard]] auto get(Headers const& headers, std::string const& key)
    -> std::string;

/// Read all HTTP Header field bytes from \p socket using \p buffer.
/** buffer is needed as parameter because this uses boost::read_until, which
 *  might read more bytes than returned, into buffer, which can be read next.
 *  Throws boost::system::system_error if there is an issue reading. */
[[nodiscard]] auto read_header_field_bytes(Socket& socket, Streambuf& buffer)
    -> std::string;

/// Parses Headers from the provided \p bytes.
[[nodiscard]] auto parse_headers(std::string_view bytes) -> Headers;

/// Create a properly formatted and valid HTTP Header fields string.
[[nodiscard]] auto to_string(Headers const& x) -> std::string;

/// Stream insertion operator overload for Headers.
auto operator<<(std::ostream& os, Headers const& x) -> std::ostream&;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_HEADERS_HPP
