#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>

#include "messagestatus.h"

using TimePoint = std::chrono::system_clock::time_point;

struct Message {
    std::string id;
    std::string chat_id;
    std::string sender_id;
    std::string sender_name;
    std::string content;
    TimePoint created_at;
    bool is_outgoing;

    MessageStatus status = MessageStatus::Sent;
};

#endif // MESSAGE_H
