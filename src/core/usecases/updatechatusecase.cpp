#include "updatechatusecase.h"

#include "core/ports/chats_service.h"

UpdateChatUseCase::UpdateChatUseCase(ChatsService* srv)
    : QObject{nullptr}
    , srv_{srv}
{
    connect(srv_, &ChatsService::updateChatInfoFinished, this,
            [this](std::expected<Chat, Error> res) {
        emit requestFinished(res, av_data_tmp_);
    });
}

void UpdateChatUseCase::execute(
    const Chat& c,
    const std::vector<std::byte>& avatar_bytes
) {
    av_data_tmp_.img_data = avatar_bytes;
    av_data_tmp_.user_id = c.id;
    av_data_tmp_.mime_type = "PNG";
    srv_->updateChatInfo(c, avatar_bytes);
}
