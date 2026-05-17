#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <chrono>
#include <vector>

#include "core/domain/message.h"

using TimePoint = std::chrono::system_clock::time_point;

struct Chat {
    enum class Type {
        Dialog,
        Group,
    };

    std::string id;
    std::string name;
    int unread_count;
    Type type;
    TimePoint created_at;
    TimePoint updated_at;

    std::vector<Message> messages;
    std::string avatar;
    std::string last_message;
};

#endif // CHAT_H
