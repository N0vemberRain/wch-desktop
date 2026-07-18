#include "loadchatsforcurrentuserusecase.h"

#include "core/ports/chats_service.h"

LoadChatsForCurrentUserUseCase::LoadChatsForCurrentUserUseCase(ChatsService* srv)
    : QObject{nullptr}
    , srv_(srv)
{
    connect(srv_, &ChatsService::getChatsListFinished, this,
            [this](auto res) {
                emit requestFinished(res);
    });
}

void LoadChatsForCurrentUserUseCase::execute(const UserID& user_id) {
    srv_->getChatsList(user_id);
}