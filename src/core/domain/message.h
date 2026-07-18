#pragma once

#include <string>
#include <chrono>

#include "messagestatus.h"

using TimePoint = std::chrono::system_clock::time_point;

struct Message {
    Message() = default;
    Message(Message&&) noexcept = default;
    Message& operator=(Message&&) noexcept = default;

    Message(const Message&) = default;
    Message& operator=(const Message&) = default;

    bool operator==(const Message&) const = default;

    std::string id;
    std::string chat_id;
    std::string sender_id;
    std::string sender_name;
    std::string content;
    TimePoint created_at;
    bool is_outgoing;

    MessageStatus status = MessageStatus::Sent;
};
