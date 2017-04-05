#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace tal {

class Message {
   public:
    explicit Message(std::string message_body);
    explicit operator std::string() const;
    enum Type { Unknown, Event, User };
    std::string get(const std::string& key) const;

   private:
    Type object_type_;
    void deduce_type();
    std::string message_body_;
};

inline std::ostream& operator<<(std::ostream& os, const Message& m) {
    return os << static_cast<std::string>(m);
}

}  // namespace tal
#endif  // MESSAGE_HPP
