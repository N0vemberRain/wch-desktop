#include "updatechatusecase.h"

#include "core/ports/chats_service.h"

UpdateChatUseCase::UpdateChatUseCase(ChatsService* srv)
    : QObject{nullptr}
    , srv_{srv}
{
    connect(srv_, &ChatsService::updateChatInfoFinished, this,
            [this](std::expected<Chat, Error> res) {
        emit requestFinished(res);
    });
}

void UpdateChatUseCase::execute(
    const Chat& c,
    const std::vector<std::byte>& avatar_bytes
) {
    srv_->updateChatInfo(c, avatar_bytes);
}
