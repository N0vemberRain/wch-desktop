#pragma once

#include <QObject>

#include <expected>

#include "core/domain/chat.h"
#include "core/domain/errors.h"
#include "core/domain/types.h"

class ChatsService;

class UpdateChatUseCase : public QObject
{
    Q_OBJECT
public:
    explicit UpdateChatUseCase(ChatsService* srv);

    void execute(const Chat& c, const std::vector<std::byte>& avatar_bytes);

signals:
    void requestFinished(std::expected<Chat, Error>, const AvatarData& av_data);

private:
    ChatsService* srv_;
    AvatarData av_data_tmp_;
};

