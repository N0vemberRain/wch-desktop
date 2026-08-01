#include "qtchatsservice.h"

#include "utils.h"
#include "mock/mockchatfactory.h"

#include <QUrl>
#include <QGrpcHttp2Channel>
#include <QGrpcCallReply>
#include <QGrpcStatus>

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

void QtChatsService::getChatsList(const UserID& id) {
    chats::v1::ListChatsForUserRequest request;
    request.setUserId(QString::fromStdString(id));

    reply_ = std::move(client_->ListChatsForUser(request, options_));
    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onGetChatsListFinished);
}

void QtChatsService::getAvatarsForChats(const std::list<ChatID>& ids) {
    // chats::v1::ListAvatarsForChatsRequest request;

    // QStringList qids{};
    // std::ranges::copy(qids, std::back_inserter(qids));

    // request.setIds(qids);

    // reply_ = std::move(client_->ListAvatarsForChats(request, options_));
    // connect(reply_.get(), &QGrpcCallReply::finished, this,
    //         &QtChatsService::onGetAvatarsForUsers);
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

        std::list<ChatID> ids;
        std::transform(chats.cbegin(), chats.cend(), std::back_inserter(ids),
                       [](const Chat& c) { return c.id; });
        getAvatarsForChats(ids);
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

    auto resp = reply_->read<UpdateChatResponse>();
    if (resp.has_value()) {
        emit updateChatInfoFinished(chat_tmp_);
    } else {
        emit getChatsListFinished(std::unexpected(
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

    return error;
}

void QtChatsService::onGetAvatarsForUsers(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit getAvatarsForChatsFinished(std::unexpected(errorHandle(s)));
        return;
    }

    // auto resp = reply_->read<GetAvatarsResponse>();
    // if (resp.has_value()) {
    //     auto& avs = resp.value().avatars();
    //     std::vector<AvatarData> res;
    //     std::transform(
    //         std::make_move_iterator(avs.begin()),
    //         std::make_move_iterator(avs.end()),
    //         std::back_inserter(res),
    //         [](const chats::v1::Avatar& av) {
    //             AvatarData a;
    //             a.img_data = toBytes(av.data());
    //             a.mime_type = av.mimeType().toStdString();
    //             a.user_id = av.ownerId().toStdString();

    //             return a;
    //         }
    //     );

    //     emit getAvatarsForChatsFinished(res);
    // } else {
    //     emit getChatsListFinished(std::unexpected(
    //         Error{ErrorCode::Unknown, "Unknown error"}));
    // }
}