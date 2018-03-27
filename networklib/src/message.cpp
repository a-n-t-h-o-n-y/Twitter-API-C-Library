#include <networklib/message.hpp>

#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace tal {

Message::Message(std::string message_body) : message_body_{message_body} {
    deduce_type();
}

Message::operator std::string() const {
    return message_body_;
}

void Message::deduce_type() {
    object_type_ = Type::Unknown;
}
void Message::build_ptree() const {
    json_tree_ptr_ = std::make_unique<boost::property_tree::ptree>();
    std::stringstream ss{message_body_};
    boost::property_tree::read_json(ss, *json_tree_ptr_);
}

boost::property_tree::ptree Message::ptree() const {
    if (json_tree_ptr_ == nullptr) {
        this->build_ptree();
    }
    return *json_tree_ptr_;
}

boost::property_tree::ptree& Message::ptree() {
    if (json_tree_ptr_ == nullptr) {
        this->build_ptree();
    }
    return *json_tree_ptr_;
}

std::string Message::get(const std::string& key) const {
    if (json_tree_ptr_ == nullptr) {
        this->build_ptree();
    }
    return json_tree_ptr_->get<std::string>(key, "");
}

}  // namespace tal
