#include <networklib/detail/read_buffer.hpp>

#include <cstddef>
#include <istream>
#include <string>

#include <networklib/detail/socket_stream.hpp>

namespace network::detail {

auto read_buffer(Streambuf& buffer, std::size_t count) -> std::string
{
    auto stream = std::istream{&buffer};
    auto result = std::string(count, '\n');
    stream.read(result.data(), count);
    return result;
}

auto flush_buffer(Streambuf& buffer) -> std::string
{
    return read_buffer(buffer, buffer.size());
}

}  // namespace network::detail
