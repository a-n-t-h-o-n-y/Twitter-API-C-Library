#ifndef NETWORKLIB_DETAIL_STATUS_LINE_HPP
#define NETWORKLIB_DETAIL_STATUS_LINE_HPP
#include <ostream>
#include <string>
#include <string_view>

#include <networklib/detail/socket_stream.hpp>
#include <networklib/socket.hpp>

namespace network::detail {

struct Status_line {
    std::string HTTP_version;
    std::string status_code;
    std::string reason_phrase;
};

/// Throws std::runtime_error exception if HTTP resonse is not 200.
void check_status(Status_line const& status);

/// Read all HTTP status line bytes from \p socket using \p buffer.
/** buffer is needed as parameter because this uses boost::read_until, which
 *  might read more bytes than returned, into buffer, which can be read next.
 *  Throws boost::system::system_error if there is an issue reading. */
[[nodiscard]] auto read_status_line_bytes(Socket& socket, Streambuf& buffer)
    -> std::string;

/// Parses a Status_line from the provided \p bytes.
[[nodiscard]] auto parse_status_line(std::string_view bytes) -> Status_line;

/// Create a properly formatted and valid HTTP status line string.
[[nodiscard]] auto to_string(Status_line const& x) -> std::string;

/// Stream insertion operator overload for Status_line.
auto operator<<(std::ostream& os, Status_line const& x) -> std::ostream&;

}  // namespace network::detail
#endif  // NETWORKLIB_DETAIL_STATUS_LINE_HPP
