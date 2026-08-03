#pragma once

#include "core/ports/chats_service.h"

#include <QGrpcCallOptions>

#include <memory>

#include "chats_client.grpc.qpb.h"
#include "core/domain/errors.h"

class QGrpcHttp2Channel;
class QGrpcCallReply;
class QGrpcStatus;

class QtChatsService : public ChatsService
{
public:
    QtChatsService();
    ~QtChatsService() override = default;

    void getChatsList(const UserID& id) override;
    void getAvatarsForChats(const std::list<ChatID>& ids) override;

    void addOption(const std::string& key,
                   const std::string& value,
                   const std::string& key_param="") override;
    void updateChatInfo(const Chat& c,
                        const std::vector<std::byte>& av_data) override;
private slots:
    void onGetChatsListFinished(const QGrpcStatus& s);
    void onUpdateChatFinished(const QGrpcStatus& s);
    void onGetAvatarsForUsers(const QGrpcStatus& s);
private:
    Error errorHandle(const QGrpcStatus& s);

    using GetChatsResponse = chats::v1::ListChatsForUserResponse;
    using GetAvatarsResponse = chats::v1::ListAvatarsForChatsResponse;
    using UpdateChatResponse = chats::v1::ChatResponse;
    using Client = chats::v1::ChatsService::Client;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;
    std::unique_ptr<QGrpcCallReply> reply_;

    QGrpcCallOptions options_;
    Chat chat_tmp_;
};
