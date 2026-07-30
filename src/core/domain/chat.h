#pragma once

#include <string>
#include <chrono>
#include <vector>

#include "core/domain/message.h"

using TimePoint = std::chrono::system_clock::time_point;

struct Chat {
    enum class Type {
        Direct,
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

    static int typeToInt(Chat::Type t) noexcept {
        if (t == Type::Direct) return 0;

        return 1;
    }
    static Chat::Type typeFromInt(int t) noexcept {
        return t == 0 ? Type::Direct : Type::Group;
    }
    static Chat::Type typeFromString(const std::string& type) noexcept {
        if (type == "group") return Chat::Type::Direct;
        return Chat::Type::Direct;
    }
    static std::string typeToString(Chat::Type t) noexcept {
        return t == Chat::Type::Group ? "group" : "direct";
    }
};
