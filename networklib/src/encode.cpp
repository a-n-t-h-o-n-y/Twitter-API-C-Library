#include <networklib/detail/encode.hpp>

#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

namespace network::detail {

auto key_value_encode(
    std::vector<std::pair<std::string, std::string>> const& parameters)
    -> std::string
{
    auto ss        = std::ostringstream{};
    auto separator = std::string{""};
    for (auto& key_value : parameters) {
        ss << separator << key_value.first << '='
           << url_encode(key_value.second);
        separator = "&";
    }
    return ss.str();
}

auto url_encode(std::string_view text) -> std::string
{
    auto ss = std::ostringstream{};
    for (unsigned char c : text) {
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') || c == '-' || c == '.' || c == '_' ||
            c == '~') {
            ss << c;
        }
        else {
            ss << '%';
            ss << std::hex << std::uppercase << std::setfill('0')
               << std::setw(2);
            ss << static_cast<int>(c);
            ss << std::nouppercase << std::setw(0);
        }
    }
    return ss.str();
}

auto base64_encode(std::vector<unsigned char> const& message) -> std::string
{
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* bio = BIO_new(BIO_s_mem());
    bio      = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, message.data(), message.size());
    BIO_flush(bio);
    auto buffer_ptr = (BUF_MEM*)nullptr;
    BIO_get_mem_ptr(bio, &buffer_ptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    auto const result = std::string(buffer_ptr->data, buffer_ptr->length);
    BUF_MEM_free(buffer_ptr);
    return result;
}

}  // namespace network::detail
