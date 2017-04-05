#include "message.hpp"

#include <string>
#include <sstream>
#include <ostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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

std::string Message::get(const std::string& key) const {
    boost::property_tree::ptree json_tree; // should be member variable
    std::istringstream ss(message_body_);
    boost::property_tree::read_json(ss, json_tree);
    return json_tree.get<std::string>(key);
}

}  // namespace tal
