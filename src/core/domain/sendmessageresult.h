#ifndef SENDMESSAGERESULT_H
#define SENDMESSAGERESULT_H

#include <string>
#include <optional>

#include "message.h"

struct SendMessageResult {
    bool ok;
    std::string error;

    std::optional<Message> message;
};

#endif // SENDMESSAGERESULT_H
