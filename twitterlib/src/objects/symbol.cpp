#include <twitterlib/objects/symbol.hpp>

#include <string>

#include <twitterlib/detail/utility.hpp>
#include <twitterlib/objects/indices.hpp>

namespace twitter {

auto to_string(Symbol const& symbol) -> std::string
{
    auto x = std::string{};
    x.append("indices: ").append(to_string(symbol.indices));
    x.append("\ntext: ").append(symbol.text);
    return x;
}

auto parse_symbol(boost::property_tree::ptree const& tree) -> Symbol
{
    auto x    = Symbol{};
    x.indices = parse_indices(tree.get_child("indices", {}));
    x.text    = tree.get<std::string>("text", {});
    return x;
}

}  // namespace twitter
