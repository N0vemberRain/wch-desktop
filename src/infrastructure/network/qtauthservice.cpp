#include "qtauthservice.h"

#include "utils.h"

#include <QUrl>
#include <QMessageBox>

#include <expected>


QtAuthService::QtAuthService()
{
    channel_ = std::make_shared<QGrpcHttp2Channel>(
        QUrl{"http://localhost:8087"}
    );

    client_ = std::make_unique<Client>();
    if (!client_->attachChannel(channel_)) {
        QMessageBox::warning(nullptr, "QtAuthService", "can't attach to the auth channel");
    }
}

void QtAuthService::login(const std::string &name, const std::string &password) {
    // if (name == "test" && password == "123") {
    //     User u;
    //     u.id = "123";
    //     u.name = "test";
    // }

    auth::v1::LoginRequest request;
    request.setEmail(QString::fromStdString(name));
    request.setPassword(QString::fromStdString(password));

    reply_ = std::move(client_->Login(request));
    connect(reply_.get(), &QGrpcCallReply::finished, this, &QtAuthService::onLoginFinished);
}

void QtAuthService::onLoginFinished(const QGrpcStatus& status) {
    AuthError err;
    if (!status.isOk()) {
        switch(status.code()) {
        case QtGrpc::StatusCode::NotFound:
            err = AuthError::InvalidCredentials;
            break;
        case QtGrpc::StatusCode::Cancelled:
            err = AuthError::AccountLocked;
            break;
        case QtGrpc::StatusCode::Internal:
            err = AuthError::NetworkError;
            break;
        default:
            err = AuthError::NetworkError;
        }

        emit loginFinished(std::unexpected(err));
        return;
    }

    auto data = reply_->read<auth::v1::LoginResponse>();
    if (data.has_value()) {
        Token t;
        const auto& tokenDTO = data.value().accessToken();
        t.value = tokenDTO.value().toStdString();
        t.user_id = tokenDTO.userId().toStdString();
        t.expires_at = fromQString(tokenDTO.expiresAt());

        emit loginFinished(t);
        return;
    }

    emit loginFinished(std::unexpected(AuthError::NetworkError));
    return;
}