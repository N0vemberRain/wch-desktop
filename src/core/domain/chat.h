#pragma once

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

    Chat() = default;
    Chat(Chat&&) noexcept = default;
    Chat& operator=(Chat&&) noexcept = default;

    Chat(const Chat&) = default;
    Chat& operator=(const Chat&) = default;

    bool operator==(const Chat&) const = default;


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
