#include <networklib/detail/encode.hpp>

#include <iomanip>
#include <ios>
#include <iostream>  // temp
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace tal {
namespace detail {

std::string key_value_encode(
    const std::vector<std::pair<std::string, std::string>>& parameters) {
    std::stringstream result;
    std::string seperator{""};
    for (auto& key_value : parameters) {
        result << seperator << key_value.first << '='
               << url_encode(key_value.second);
        seperator = "&";
    }
    return result.str();
}

std::string url_encode(const std::string& text) {
    std::stringstream result;
    for (char c : text) {
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') || c == '-' || c == '.' || c == '_' ||
            c == '~') {
            result << c;
        } else {
            result << '%';
            result << std::hex << std::uppercase << std::setfill('0')
                   << std::setw(2);
            result << static_cast<int>(c);
            result << std::nouppercase << std::setw(0);
        }
    }
    return result.str();
}

std::string base64_encode(const std::vector<unsigned char>& message) {
    BIO *bio, *b64;
    BUF_MEM* bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, message.data(), message.size());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    std::string result(bufferPtr->data, bufferPtr->length);
    BUF_MEM_free(bufferPtr);
    return result;
}

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
}  // namespace tal
