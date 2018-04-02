#include <networklib/response.hpp>

#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <networklib/view_ptree.hpp>

namespace network {

Response::Response(std::string message_body) : message_body_{message_body} {
    deduce_type();
}

Response::operator std::string() const {
    return message_body_;
}

void Response::deduce_type() {
    object_type_ = Type::Unknown;
}
void Response::build_ptree() const {
    json_tree_ptr_ = std::make_unique<boost::property_tree::ptree>();
    std::stringstream ss{message_body_};
    boost::property_tree::read_json(ss, *json_tree_ptr_);
}

const boost::property_tree::ptree& Response::ptree() const {
    if (json_tree_ptr_ == nullptr) {
        this->build_ptree();
    }
    return *json_tree_ptr_;
}

boost::property_tree::ptree& Response::ptree() {
    if (json_tree_ptr_ == nullptr) {
        this->build_ptree();
    }
    return *json_tree_ptr_;
}

std::string Response::get(const std::string& key) const {
    if (json_tree_ptr_ == nullptr) {
        this->build_ptree();
    }
    return json_tree_ptr_->get<std::string>(key, "");
}

std::ostream& operator<<(std::ostream& os, const Response& m) {
    network::view_ptree(m.ptree(), os);
    return os;
}

}  // namespace network
