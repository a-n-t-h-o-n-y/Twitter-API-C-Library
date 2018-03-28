#include <networklib/detail/gzip.hpp>

#include <string>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace network {
namespace detail {

/// Decodes a gzip archive, for use with encoded message bodies.
void decode_gzip(std::string& zipped) {
    std::string decoded;
    boost::iostreams::filtering_ostream f_os;
    f_os.push(boost::iostreams::gzip_decompressor());
    f_os.push(boost::iostreams::back_inserter(decoded));

    boost::iostreams::write(f_os, &zipped[0], zipped.size());
    boost::iostreams::close(f_os);
    zipped = decoded;
}

}  // namespace detail
}  // namespace network
