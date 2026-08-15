#pragma once

#include <QObject>

#include <expected>
#include <optional>
#include <list>

#include "core/domain/types.h"
#include "core/domain/chat.h"
#include "core/domain/chat_participant.h"
#include "core/domain/errors.h"

class ChatsService : public QObject {
    Q_OBJECT
public:
    virtual ~ChatsService() = default;

    virtual void createGroupChat(
        const Chat& c,
        const std::vector<std::byte>& av_data) = 0;
    virtual void createDirectChat(const UserID& user_id) = 0;
    virtual void getChatsList(const UserID& id) = 0;
    // std::pair - chat id, is chat direct
    virtual void getAvatarsForChats(const std::list<std::pair<ChatID, bool>>& ids) = 0;
    virtual void addOption(const std::string& key,
                           const std::string& value,
                           const std::string& key_param="") = 0;
    virtual void updateChatInfo(const Chat& c,
                                const std::vector<std::byte>& av_data) = 0;

    virtual void listChatParticipants(const ChatID& chat_id) = 0;
signals:
    void getChatsListFinished(std::expected<std::list<Chat>, Error>);
    void getAvatarsForChatsFinished(std::expected<std::vector<AvatarData>, Error>);
    void updateChatInfoFinished(std::expected<Chat, Error>);
    void createChatFinished(std::expected<std::pair<Chat, std::optional<AvatarData>>, Error>);

    void listChatParticipantsFinished(std::expected<std::list<ChatParticipant>, Error> res);
};
