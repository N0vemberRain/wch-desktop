#pragma once

#include <QObject>

#include <list>
#include <expected>

#include "core/domain/chat.h"
#include "core/domain/errors.h"
#include "core/domain/types.h"

class ChatsService;

class LoadChatsForCurrentUserUseCase : public QObject
{
    Q_OBJECT
public:
    explicit LoadChatsForCurrentUserUseCase(ChatsService* srv);

    void execute(const UserID& user_id);
signals:
    void requestFinished(std::expected<std::list<Chat>, Error> res);
private:
    ChatsService* srv_;
};
