#include "qtusersservice.h"

#include "core/domain/types.h"
#include "core/domain/errors.h"
#include "utils.h"

#include <QtGrpc/QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>
#include <QtGrpc/QGrpcStatus>
#include <QUrl>
#include <QMessageBox>

QtUsersService::QtUsersService() {
    channel_ = std::make_shared<QGrpcHttp2Channel>(
        QUrl{"http://localhost:8082"}
    );

    client_ = std::make_unique<Client>();
    if (!client_->attachChannel(channel_)) {
        QMessageBox::warning(nullptr, "QtUsersService", "can't attach to the users channel");
    }
}

void QtUsersService::getUser(const UserID& id) {
    users::v1::GetUserByIDRequest request;
    request.setUserId(QString::fromStdString(id));

    reply_ = std::move(client_->GetUserByID(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtUsersService::onGetUserFinished);
}


void QtUsersService::onGetUserFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit loadCurrentUserFinished(std::unexpected(errorHandle(s)));
        return;
    }

    emit loadCurrentUserFinished(to_expected(reply_->read<Response>()
        .and_then([](Response&& resp) {
            User u;
            u.id = resp.user().id_proto().toStdString();
            u.name = resp.user().username().toStdString();
            u.email = resp.user().email().toStdString();

            return std::optional<User>(u);
    }), Error{ErrorCode::Unknown, "Unknown Error"}));
}

void QtUsersService::addOption(const std::string& key, const std::string& value, const std::string& value_param) {
    QByteArray bytes;
    if (value_param.empty()) {
        bytes = QByteArray::fromStdString(value);
    } else {
        bytes = QByteArray::fromStdString(value_param + " " + value);
    }
    options_.addMetadata(QByteArray::fromStdString(key), bytes);
}

void QtUsersService::updateUser(const User& u) {

    new_avatar_path_ = QString::fromStdString(u.avatar_url);

    users::v1::UpdateUserRequest request;
    users::v1::User dto;
    dto.setUsername(QString::fromStdString(u.name));
    dto.setAvatarUrl(QString::fromStdString(u.avatar_url));
    dto.setEmail(QString::fromStdString(u.email));
    dto.setId_proto(QString::fromStdString(u.id));

    request.setUser(dto);

    reply_ = std::move(client_->UpdateUser(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtUsersService::onUpdateUserFinished);
}

void QtUsersService::updateUser(const User& u, const std::vector<std::byte>& av_data) {
    new_avatar_path_ = QString::fromStdString(u.avatar_url);

    users::v1::UpdateUserRequest request;
    users::v1::User dto;
    dto.setUsername(QString::fromStdString(u.name));
    dto.setAvatarUrl(QString::fromStdString(u.avatar_url));
    dto.setEmail(QString::fromStdString(u.email));
    dto.setId_proto(QString::fromStdString(u.id));
    request.setUser(dto);

    users::v1::Avatar av_dto;
    av_dto.setData(toQByteArray(av_data));
    av_dto.setMimeType("PNG");
    request.setAvatar(av_dto);

    reply_ = std::move(client_->UpdateUser(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished, this,
            &QtUsersService::onUpdateUserFinished);
}

void QtUsersService::onUpdateUserFinished(const QGrpcStatus& s) {
    if (!s.isOk()) {
        emit currentUserChanged(std::unexpected(errorHandle(s)));
        // User u;
        // u.name = "Igor";
        // u.avatar_url = new_avatar_path_.toStdString();
        // emit currentUserChanged(u);
        return;
    }

    emit currentUserChanged(to_expected(reply_->read<Response>()
        .and_then([](Response&& resp) {
            User u;
            u.id = resp.user().id_proto().toStdString();
            u.name = resp.user().username().toStdString();
            u.email = resp.user().email().toStdString();

            return std::optional<User>(u);
    }), Error{ErrorCode::Unknown, "Unknown Error"}));
}

Error QtUsersService::errorHandle(const QGrpcStatus& s) {
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

void QtUsersService::requestAvatar(const UserID& user_id) {
    users::v1::GetAvatarRequest request;
    request.setUserId(QString::fromStdString(user_id));

    reply_ = std::move(client_->GetAvatarForUser(request, options_));

    connect(reply_.get(), &QGrpcCallReply::finished,
            this, &QtUsersService::onGetAvatarFinished);
}

void QtUsersService::onGetAvatarFinished(const QGrpcStatus& status) {
    if (!status.isOk()) {
        emit getAvatarFinished(std::unexpected(errorHandle(status)));
        return;
    }

    emit getAvatarFinished(to_expected(reply_->read<GetAvatarResponse>()
        .and_then([](GetAvatarResponse&& resp) {
            AvatarData data;
            data.user_id = resp.userId().toStdString();
            data.img_data = toBytes(resp.avatar().data());
            data.mime_type = resp.avatar().mimeType().toStdString();
            return std::optional<AvatarData>(data);
    }), Error{ErrorCode::Unknown, "Unknown Error"}));
}
