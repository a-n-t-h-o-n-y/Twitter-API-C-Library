#include <networklib/detail/parse.hpp>

#include <istream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <networklib/detail/types.hpp>

namespace tal {
namespace detail {

std::string read_chunk(ssl_socket& socket, boost::asio::streambuf& buffer) {
    // boost::asio::streambuf buffer;
    boost::system::error_code ec;
    // Read size
    // deadline for timeout operation.
    boost::asio::read_until(socket, buffer, "\r\n", ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream stream(&buffer);
    std::string chunk_size_str;
    stream >> chunk_size_str;
    if (chunk_size_str.empty()) {
        return " ";
    }
    auto chunk_size = std::stoul(chunk_size_str, nullptr, 16);
    std::string trash(2, ' ');
    stream.read(&trash[0], 2);  // remove "/r/n"

    // Read chunk
    auto read_n = boost::asio::read(
        socket, buffer, boost::asio::transfer_exactly(chunk_size), ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::string chunk(read_n, ' ');
    stream.read(&chunk[0], read_n);

    // Remove last "\r\n"
    boost::asio::read(socket, buffer, boost::asio::transfer_exactly(2), ec);
    stream.read(&trash[0], 2);  // remove "/r/n"
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    return chunk;
}

std::string read_length(ssl_socket& socket,
                        std::size_t n,
                        boost::asio::streambuf& buffer) {
    // boost::asio::streambuf buffer;
    boost::system::error_code ec;
    auto read_n =
        boost::asio::read(socket, buffer, boost::asio::transfer_exactly(n), ec);
    if (ec && ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
    }
    std::istream stream(&buffer);
    std::string message(read_n, ' ');
    stream.read(&message[0], read_n);
    return message;
}

}  // namespace detail
}  // namespace tal
