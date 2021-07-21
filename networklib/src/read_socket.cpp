#include <networklib/detail/read_socket.hpp>

#include <istream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/ssl.hpp>

#include <networklib/detail/read_buffer.hpp>
#include <networklib/detail/socket_stream.hpp>
#include <networklib/socket.hpp>

namespace network::detail {

auto read_chunk(Socket& socket, Streambuf& buffer) -> std::string
{
    boost::asio::read_until(socket.get(), buffer, "\r\n");

    auto stream         = std::istream{&buffer};
    auto chunk_size_str = std::string{};
    stream >> chunk_size_str;
    if (chunk_size_str.empty())
        return " ";

    auto const chunk_size = std::stoul(chunk_size_str, nullptr, 16);
    {
        auto trash = std::string(2, ' ');
        stream.read(trash.data(), 2);  // remove "/r/n"
    }

    // Read chunk
    auto n = boost::asio::read(socket.get(), buffer,
                               boost::asio::transfer_exactly(chunk_size));

    auto chunk = std::string(n, ' ');
    stream.read(chunk.data(), n);

    // Remove last "\r\n"
    boost::asio::read(socket.get(), buffer, boost::asio::transfer_exactly(2));
    {
        auto trash = std::string(2, ' ');
        stream.read(trash.data(), 2);  // remove "/r/n"
    }
    return chunk;
}

auto read_length(Socket& socket, Streambuf& buffer, std::size_t n)
    -> std::string
{
    auto const read_n = boost::asio::read(socket.get(), buffer,
                                          boost::asio::transfer_exactly(n));
    return read_buffer(buffer, read_n);
}

}  // namespace network::detail
