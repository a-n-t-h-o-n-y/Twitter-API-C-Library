#include <twitterlib/objects/indices.hpp>

#include <boost/property_tree/ptree.hpp>

#include <twitterlib/objects/utility.hpp>

namespace twitter {

auto to_string(Indices const& indices) -> std::string
{
    auto x = std::string{};
    x.append(1, '[')
        .append(to_string(indices[0]))
        .append(", ")
        .append(to_string(indices[1]))
        .append(1, ']');
    return x;
}

auto parse_indices(boost::property_tree::ptree const& tree) -> Indices
{
    auto x         = Indices{};
    auto const vec = as_vector<int>(tree);
    if (vec.size() == 2) {
        x[0] = vec[0];
        x[1] = vec[1];
    }
    return x;
}

}  // namespace twitter
