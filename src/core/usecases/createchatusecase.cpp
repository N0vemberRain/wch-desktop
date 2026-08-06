#include "createchatusecase.h"

#include "core/ports/chats_service.h"

CreateChatUseCase::CreateChatUseCase(ChatsService* srv)
    : QObject{nullptr}
    , srv_{srv}
{
    connect(srv_, &ChatsService::createChatFinished, this,
            [this](std::expected<std::pair<Chat, std::optional<AvatarData>>, Error> res) {
        emit requestFinished(res);
    });
}

void CreateChatUseCase::execute(const Chat& c, const std::vector<std::byte>& avatar_bytes) {
    srv_->createGroupChat(c, avatar_bytes);
}

void CreateChatUseCase::execute(const UserID& user_id) {
    srv_->createDirectChat(user_id);
}