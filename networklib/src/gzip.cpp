#include <networklib/detail/gzip.hpp>

#include <string>
#include <string_view>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace network::detail {

/// Decodes a gzip archive, for use with encoded message bodies.
auto decode_gzip(std::string_view zipped) -> std::string
{
    namespace bios = boost::iostreams;
    auto decoded   = std::string{};
    auto f_os      = bios::filtering_ostream{};

    f_os.push(bios::gzip_decompressor());
    f_os.push(bios::back_inserter(decoded));

    bios::write(f_os, &zipped[0], zipped.size());
    bios::close(f_os);
    return decoded;
}

}  // namespace network::detail
