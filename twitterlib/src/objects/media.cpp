#include <twitterlib/objects/media.hpp>

#include <cstdint>
#include <optional>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/detail/utility.hpp>
#include <twitterlib/objects/indices.hpp>
#include <twitterlib/objects/sizes.hpp>

namespace twitter {

auto to_string(Media const& media) -> std::string
{
    auto x = std::string{};
    x.append("display_url: ").append(media.display_url);
    x.append("\nexpanded_url: ").append(media.expanded_url);
    x.append("\nid: ").append(to_string(media.id));
    x.append("\nindices: ").append(to_string(media.indices));
    x.append("\nmedia_url: ").append(media.media_url);
    x.append("\nmedia_url_https: ").append(media.media_url_https);
    x.append("\nSizes:\n").append(add_indention_level(to_string(media.sizes)));
    if (media.source_status_id.has_value()) {
        x.append("\nsource_status_id: ")
            .append(to_string(media.source_status_id.value()));
    }
    x.append("\ntype: ").append(media.type);
    x.append("\nurl: ").append(media.url);
    return x;
}

auto parse_media(boost::property_tree::ptree const& tree) -> Media
{
    auto x            = Media{};
    x.display_url     = tree.get<std::string>("display_url", {});
    x.expanded_url    = tree.get<std::string>("expanded_url", {});
    x.id              = tree.get<std::int64_t>("id", -1);
    x.indices         = parse_indices(tree.get_child("indices", {}));
    x.media_url       = tree.get<std::string>("media_url", {});
    x.media_url_https = tree.get<std::string>("media_url_https", {});
    x.sizes           = parse_sizes(tree.get_child("sizes", {}));
    x.source_status_id =
        to_std(tree.get_optional<std::int64_t>("source_status_id"));
    x.type = tree.get<std::string>("type", {});
    x.url  = tree.get<std::string>("url", {});
    return x;
}

}  // namespace twitter
