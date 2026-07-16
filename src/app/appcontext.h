#pragma once

#include <QObject>

#include <memory>

#include "core/usecases/loginusecase.h"
#include "core/usecases/loadcurrentuserusecase.h"
#include "core/usecases/sendmessageusecase.h"
#include "core/usecases/updateprofileusecase.h"
#include "app/sessionmanager.h"
#include "core/ports/session_storage.h"
#include "infrastructure/utils/avatarprovider.h"

class AuthService;
class UsersService;
class MessageService;

class AppContext : public QObject
{
    Q_OBJECT
public:
    AppContext(std::unique_ptr<AuthService> as,
               std::unique_ptr<UsersService> us,
               std::unique_ptr<MessageService> ms,
               std::unique_ptr<SessionStorage> ses_storage,
                std::unique_ptr<LoginUseCase> login_use_case,
               SessionManager&& session_manager);
    ~AppContext();

    bool hasSession() const noexcept {
        return session_manager.hasSession();
    }

    void setupCurrentUserProfile();

    SessionManager session_manager;
    std::unique_ptr<SessionStorage> session_storage;

    std::unique_ptr<AuthService> auth_service;
    std::unique_ptr<UsersService> users_service;
    std::unique_ptr<MessageService> msgs_service;

    std::unique_ptr<LoginUseCase> login_use_case;
    LoadCurrentUserUseCase load_current_user_use_case;
    SendMessageUseCase send_msgs_use_case;
    UpdateProfileUseCase update_profile_uc;
    AvatarProvider av_provider;


    inline bool isLoading() const noexcept {
        return is_loading_;
    }

signals:
    void loadingFinished();
    void currentUserChanged(const User& u);
private slots:
    void onLoadCurrentUserFinished(std::expected<User, Error> res);

private:
    bool is_loading_ {false};
};

