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

void QtChatsService::getChatsList(const UserID& id) {
    chats::v1::GetChatsByUserIDRequest request;
    request.setUserId(QString::fromStdString(id));

    reply_ = std::move(client_->GetChatsByUserID(request));
    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtChatsService::onGetChatsListFinished);
}

void QtChatsService::onGetChatsListFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        // emit getChatsListFinished(std::unexpected(errorHandle(s)));
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
            c.type = c_dto.type() == "Group" ?
                         Chat::Type::Group :
                         Chat::Type::Dialog;
            c.updated_at = fromQString(c_dto.updatedAt());
            chats.emplace_back(c);
        }

        emit getChatsListFinished(chats);
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