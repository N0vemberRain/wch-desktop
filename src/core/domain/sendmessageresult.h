#pragma once

#include <string>
#include <optional>

#include "message.h"

struct SendMessageResult {
    bool ok;
    std::string error;

    std::optional<Message> message;
};
