#pragma once

#include <QObject>

#include <memory>

#include "core/usecases/loginusecase.h"
#include "core/usecases/loadcurrentuserusecase.h"
#include "core/usecases/sendmessageusecase.h"
#include "core/usecases/updateprofileusecase.h"
#include "core/usecases/loadchatsforcurrentuserusecase.h"
#include "core/usecases/updatechatusecase.h"
#include "core/usecases/createchatusecase.h"
#include "app/sessionmanager.h"
#include "core/ports/session_storage.h"
#include "infrastructure/utils/avatarprovider.h"

class AuthService;
class UsersService;
class MessageService;
class ChatsService;

class AppContext : public QObject
{
    Q_OBJECT
public:
    AppContext(std::unique_ptr<AuthService> as,
               std::unique_ptr<UsersService> us,
               std::unique_ptr<MessageService> ms,
               std::unique_ptr<ChatsService> cs,
               std::unique_ptr<SessionStorage> ses_storage,
                std::unique_ptr<LoginUseCase> login_use_case,
               SessionManager&& session_manager);
    ~AppContext();

    bool hasSession() const noexcept {
        return session_manager.hasSession();
    }
    const User& getCurrentUser() const noexcept;
    const UserID& getCurrentUserID() const noexcept;
    const Token& getToken() const noexcept;

    void setupCurrentUserProfile();

    inline bool isLoading() const noexcept {
        return is_loading_;
    }

    AvatarProvider* getAvatarProvider() const noexcept;
    const SendMessageUseCase& getSendMessageUC() const noexcept;
    UpdateProfileUseCase& getUpdateUserUC() noexcept;
    UpdateChatUseCase& getUpdateChatUC() noexcept {
        return update_chat_uc;
    }
    CreateChatUseCase& getCreateChatUC() noexcept {
        return create_chat_uc;
    }
signals:
    void loadingProfileFinished();
    void loadingAvatarFinished(QPixmap img);
    void loadingChatsFinished(std::expected<std::list<Chat>, Error>);
    void loadingAvatarsForChatsFinished(const QHash<QString, QPixmap>&);
    void currentUserChanged(const User& u);
    void updateChatFinished(Chat chat, QPixmap new_av);
    void createChatFinished(const Chat&, std::optional<QPixmap>);
private slots:
    void onLoadCurrentUserFinished(std::expected<User, Error> res);
    void onLoadAvatarFinished(std::expected<AvatarData, Error> res);
    void onUpdateChatFinished(std::expected<Chat, Error> res, AvatarData av);
    void onLoadChatsFinished(std::expected<std::list<Chat>, Error> res);
    void onCreateChatFinished(std::expected<std::pair<Chat, std::optional<AvatarData>>, Error> res);
private:
    SessionManager session_manager;
    std::unique_ptr<SessionStorage> session_storage;

    std::unique_ptr<AuthService> auth_service;
    std::unique_ptr<UsersService> users_service;
    std::unique_ptr<MessageService> msgs_service;
    std::unique_ptr<ChatsService> chats_service;

    std::unique_ptr<LoginUseCase> login_use_case;
    LoadCurrentUserUseCase load_current_user_use_case;
    SendMessageUseCase send_msgs_use_case;
    UpdateProfileUseCase update_profile_uc;
    LoadChatsForCurrentUserUseCase load_chats_uc;
    UpdateChatUseCase update_chat_uc;
    CreateChatUseCase create_chat_uc;

    std::unique_ptr<AvatarProvider> av_provider;
    bool is_loading_ {false};
};

