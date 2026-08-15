#pragma once

#include "core/domain/types.h"

struct ChatParticipant {
    enum class Role {
        Member,
        Admin,
        Owner,
        Unspecified
    };

    ChatID chat_id;
    UserID user_id;
    std::string name;
    Role role;
    AvatarData avatar;

    bool operator<=>(const ChatParticipant&) const = default;
};