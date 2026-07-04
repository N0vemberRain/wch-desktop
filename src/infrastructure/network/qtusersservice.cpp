#include "qtusersservice.h"

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


void QtUsersService::onGetUserFinished(const QGrpcStatus& status) {
    Error error;

    if (!status.isOk()) {
        switch (status.code()) {
        case QtGrpc::StatusCode::NotFound:
            error = Error{ErrorCode::NotFound, status.message().toStdString()};
            break;
        case QtGrpc::StatusCode::Unauthenticated:
            error = Error{ErrorCode::Unauthorized, status.message().toStdString()};
            break;
        case QtGrpc::StatusCode::PermissionDenied:
            error = Error{ErrorCode::Forbidden, status.message().toStdString()};
            break;
        case QtGrpc::StatusCode::Internal:
            error = Error{ErrorCode::ServerError, status.message().toStdString()};
        default:
            error = Error{ErrorCode::Unknown, status.message().toStdString()};
        }

        emit loadCurrentUserFinished(std::unexpected(error));
    }

    // const auto data = reply_->read<users::v1::GetUserResponse>();
    // if (data.has_value()) {

    // }
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



