#include "sendmessageusecase.h"

SendMessageUseCase::SendMessageUseCase(MessageService& srv)
    : srv_{srv}
{

}

SendMessageResult SendMessageUseCase::execute(const Message &msg) {
    if (msg.content.empty()) {
        return {false, "empty message", {}};
    }

    return srv_.sendMessage(msg);
}
