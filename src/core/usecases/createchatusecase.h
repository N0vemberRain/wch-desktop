#pragma once

#include <QObject>

#include <expected>
#include <optional>

#include "core/domain/chat.h"
#include "core/domain/errors.h"
#include "core/domain/types.h"

class ChatsService;

class CreateChatUseCase : public QObject
{
    Q_OBJECT
public:
    explicit CreateChatUseCase(ChatsService* srv);

    void execute(const Chat& c, const std::vector<std::byte>& avatar_bytes);
    void execute(const UserID& user_id);

signals:
    void requestFinished(std::expected<std::pair<Chat, std::optional<AvatarData>>, Error>);
private:
    ChatsService* srv_;
};

