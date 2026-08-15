#include "qtchatsservice.h"

#include "utils.h"
#include "mock/mockchatfactory.h"

#include <QUrl>
#include <QGrpcHttp2Channel>
#include <QGrpcCallReply>
#include <QGrpcStatus>

#include <QDebug>

QtChatsService::QtChatsService() {
    channel_ = std::make_shared<QGrpcHttp2Channel>(
        QUrl{"http://localhost:8085"}
    );

    client_ = std::make_unique<Client>();
    if (!client_->attachChannel(channel_)) {
        throw std::runtime_error{"QtChatsService: can't attach to the chats channel"};
    }
}

void QtChatsService::addOption(const std::string& key, const std::string& value, const std::string& value_param) {
    QByteArray bytes;
    if (value_param.empty()) {
        bytes = QByteArray::fromStdString(value);
    } else {
        bytes = QByteArray::fromStdString(value_param + " " + value);
    }
    options_.addMetadata(QByteArray::fromStdString(key), bytes);
}

void QtChatsService::createGroupChat(const Chat& c,
                                   const std::vector<std::byte>& av_data)
{
    chats::v1::CreateGroupChatRequest request;
    chats::v1::Avatar av_dto;
    av_dto.setOwnerId(QString::fromStdString(c.id));
    av_dto.setMimeType("PNG");
    av_dto.setData(toQByteArray(av_data));

    request.setName(QString::fromStdString(c.name));
    request.setAbout("");
    request.setAvatar(av_dto);

    reply_ = std::move(client_->CreateGroupChat(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onCreateChatFinished);

    chat_tmp_ = c;
    av_tmp_.img_data = av_data;
    av_tmp_.mime_type = "PNG";
}

void QtChatsService::createDirectChat(const UserID& user_id) {
    chats::v1::CreateDirectChatRequest request;
    request.setUserId(QString::fromStdString(user_id));

    reply_ = std::move(client_->CreateDirectChat(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onCreateChatFinished);
}

void QtChatsService::getChatsList(const UserID& id) {
    chats::v1::ListChatsForUserRequest request;
    request.setUserId(QString::fromStdString(id));

    reply_ = std::move(client_->ListChatsForUser(request, options_));
    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onGetChatsListFinished);
}

void QtChatsService::getAvatarsForChats(const std::list<std::pair<ChatID, bool>>& chats_info) {
    chats::v1::ListAvatarsForChatsRequest request;

    // std::ranges::copy(qids, std::back_inserter(qids), );
    QList<chats::v1::ChatSummary> chats;

    for (const auto& [chat_id, is_direct] : chats_info) {
        chats::v1::ChatSummary sum;
        sum.setId_proto(QString::fromStdString(chat_id));
        sum.setIsDirect(is_direct);
        chats.append(std::move(sum));
    }
    request.setChats(std::move(chats));

    reply_ = std::move(client_->ListAvatarsForChats(request, options_));
    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onGetAvatarsForUsers);
}

void QtChatsService::onGetChatsListFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit getChatsListFinished(std::unexpected(errorHandle(s)));
        // return;

        auto chats_v = MockChatFactory::getChatList(
            ":/mock_data/src/mock/data/chats_list.json");
        std::list<Chat> chats_l;
        std::ranges::move(chats_v, std::back_inserter(chats_l));

        emit getChatsListFinished(chats_l);
        return;
    }

    auto resp = reply_->read<GetChatsResponse>();
    if (resp.has_value()) {
        std::list<Chat> chats;
        foreach (auto c_dto, resp.value().chats()) {
            Chat c;
            c.id = c_dto.id_proto().toStdString();
            c.name = c_dto.name().toStdString();
            c.type = c_dto.type() == "group" ?
                         Chat::Type::Group :
                         Chat::Type::Direct;
            c.updated_at = fromQString(c_dto.updatedAt());
            chats.emplace_back(c);
        }

        emit getChatsListFinished(chats);

        std::list<std::pair<ChatID, bool>> chats_info;
        std::transform(chats.cbegin(), chats.cend(), std::back_inserter(chats_info),
                       [](const Chat& c) {
                           const auto is_direct = c.type == Chat::Type::Direct ? true : false;
                            return std::make_pair(c.id, is_direct);
        });
        getAvatarsForChats(chats_info);
    } else {
        emit getChatsListFinished(std::unexpected(
            Error{ErrorCode::Unknown, "Unknown error"}));
    }
}

void QtChatsService::updateChatInfo(
    const Chat& c,
    const std::vector<std::byte>& av_data
) {
    chats::v1::UpdateChatRequest request;
    chats::v1::Chat dto;
    dto.setName(QString::fromStdString(c.name));
    dto.setId_proto(QString::fromStdString(c.id));
    auto type = QString::fromStdString(Chat::typeToString(c.type));
    dto.setType(type);

    chats::v1::Avatar av_dto;
    av_dto.setOwnerId(QString::fromStdString(c.id));
    av_dto.setMimeType("PNG");
    av_dto.setData(toQByteArray(av_data));

    request.setChat(dto);
    request.setAvatar(av_dto);

    reply_ = std::move(client_->UpdateChat(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onUpdateChatFinished);

    chat_tmp_ = c;
}

void QtChatsService::onUpdateChatFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit updateChatInfoFinished(std::unexpected(errorHandle(s)));
        return;
    }

    auto resp = reply_->read<ChatResponse>();
    if (resp.has_value()) {
        emit updateChatInfoFinished(chat_tmp_);
    } else {
        emit getChatsListFinished(std::unexpected(
            Error{ErrorCode::Unknown, "Unknown error"}));
    }
}

void QtChatsService::onCreateChatFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit createChatFinished(std::unexpected(errorHandle(s)));
        return;
    }

    auto resp = reply_->read<ChatResponse>();
    if (resp.has_value()) {
        auto dto = resp.value().chat();
        Chat c;
        c.id = dto.id_proto().toStdString();
        c.name = dto.name().toStdString();
        c.created_at = fromQString(dto.createdAt());
        c.updated_at = c.created_at;
        c.type = dto.type() == "direct" ? Chat::Type::Direct : Chat::Type::Group;

        if (c.type == Chat::Type::Group) {
            av_tmp_.user_id = c.id;
            emit createChatFinished(std::make_pair(c, av_tmp_));
        } else {
            if (resp.value().hasAvatar()) {
                auto av = resp.value().avatar();
                AvatarData new_av;
                new_av.img_data = toBytes(av.data());
                new_av.mime_type = av.mimeType().toStdString();
                new_av.user_id = av.ownerId().toStdString();

                emit createChatFinished(std::make_pair(c, new_av));
            } else {
                emit createChatFinished(std::make_pair(c, std::nullopt));
            }
        }
    } else {
        emit createChatFinished(std::unexpected(
            Error{ErrorCode::Unknown, "Unknown error"}));
    }
}

Error QtChatsService::errorHandle(const QGrpcStatus& s) {
    Error error;
    switch (s.code()) {
    case QtGrpc::StatusCode::NotFound:
        error = Error{ErrorCode::NotFound, s.message().toStdString()};
        break;
    case QtGrpc::StatusCode::Unauthenticated:
        error = Error{ErrorCode::Unauthorized, s.message().toStdString()};
        break;
    case QtGrpc::StatusCode::PermissionDenied:
        error = Error{ErrorCode::Forbidden, s.message().toStdString()};
        break;
    case QtGrpc::StatusCode::Internal:
        error = Error{ErrorCode::ServerError, s.message().toStdString()};
    default:
        error = Error{ErrorCode::Unknown, s.message().toStdString()};
    }

    qDebug() << error.msg << "\n";
    return error;
}

void QtChatsService::onGetAvatarsForUsers(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit getAvatarsForChatsFinished(std::unexpected(errorHandle(s)));
        return;
    }

    auto resp = reply_->read<GetAvatarsResponse>();
    if (resp.has_value()) {
        auto& avs = resp.value().avatars();
        std::vector<AvatarData> res;
        std::transform(
            std::make_move_iterator(avs.begin()),
            std::make_move_iterator(avs.end()),
            std::back_inserter(res),
            [](const chats::v1::Avatar& av) {
                AvatarData a;
                a.img_data = toBytes(av.data());
                a.mime_type = av.mimeType().toStdString();
                a.user_id = av.ownerId().toStdString();

                return a;
            }
        );

        emit getAvatarsForChatsFinished(res);
    } else {
        emit getChatsListFinished(std::unexpected(
            Error{ErrorCode::Unknown, "Unknown error"}));
    }
}

void QtChatsService::listChatParticipants(const ChatID& chat_id) {
    chats::v1::ListParticipantsRequest request;
    request.setChatId(QString::fromStdString(chat_id));

    reply_ = std::move(client_->ListParticipants(request, options_));
    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onListParticipantsFinished);
}

void QtChatsService::onListParticipantsFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit listChatParticipantsFinished(std::unexpected(errorHandle(s)));
        return;
    }

    auto resp = reply_->read<ListParticipantsResponse>();
    if (!resp.has_value()) {
        emit listChatParticipantsFinished(std::unexpected(
            Error{ErrorCode::Unknown, "Unknown Error"}));
        return;
    }

    std::list<ChatParticipant> users;
    auto& users_dto = resp.value().users();
    std::ranges::transform(users_dto, std::back_inserter(users),
                           [](auto& user_dto){
                               ChatParticipant user;
        user.chat_id = user_dto.chatId().toStdString();
        user.user_id = user_dto.userId().toStdString();
        user.name = user_dto.name().toStdString();
        user.role = ChatParticipant::Role::Admin;
        if (user_dto.hasAvatar()) {
            auto av_dto = user_dto.avatar();
            AvatarData av;
            av.img_data = toBytes(av_dto.data());
            av.mime_type = av_dto.mimeType().toStdString();
            av.user_id = av_dto.ownerId().toStdString();

            user.avatar = av;
        }

        return user;
    });

    emit listChatParticipantsFinished(users);
}

void QtChatsService::addParticipant(
    const ChatID& chat_id,
    const UserID& user_id,
    ChatParticipant::Role role)
{
    chats::v1::AddParticipantRequest request;
    request.setChatId(QString::fromStdString(chat_id));
    request.setUserId(QString::fromStdString(user_id));
    request.setRole(chats::v1::ChatParticipantRoleGadget::ChatParticipantRole::CHAT_PARTICIPANT_ROLE_ADMIN);

    reply_ = std::move(client_->AddParticipant(request, options_));
    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onAddParticipantFinished);
}

void QtChatsService::onAddParticipantFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit addParticipantFinished(errorHandle(s));
        return;
    }

    auto resp = reply_->read<AddParticipantResponse>();
    if (resp.has_value()) {
        emit addParticipantFinished(std::nullopt);
    } else {
        emit addParticipantFinished(Error{ErrorCode::Unknown, "Unknown Error"});
    }
}