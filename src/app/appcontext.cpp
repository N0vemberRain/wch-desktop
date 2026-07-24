#include "appcontext.h"

#include "core/ports/authservice.h"
#include "core/ports/users_service.h"
#include "core/ports/msgservice.h"
#include "core/ports/chats_service.h"
#include "utils.h"

AppContext::AppContext(std::unique_ptr<AuthService> as,
                       std::unique_ptr<UsersService> us,
                       std::unique_ptr<MessageService> ms,
                       std::unique_ptr<ChatsService> cs,
                       std::unique_ptr<SessionStorage> ses_storage,
                       std::unique_ptr<LoginUseCase> login_use_case,
                       SessionManager&& sm)
    :
    auth_service{std::move(as)},
    users_service{std::move(us)},
    msgs_service{std::move(ms)},
    chats_service{std::move(cs)},
    session_storage{std::move(ses_storage)},
    session_manager{std::move(sm)},
    login_use_case{std::move(login_use_case)},
    load_current_user_use_case{users_service.get(), session_manager.getSession()},
    send_msgs_use_case{msgs_service.get(), session_manager.getSession()},
    update_profile_uc{users_service.get()},
    load_chats_uc{chats_service.get()},
    av_provider{*users_service.get()}
{
    if (!session_manager.hasSession()) {
        throw std::runtime_error{"session has to be initialized before AppContext"};
    }

    connect(&load_current_user_use_case, &LoadCurrentUserUseCase::loadCurrentUserFinished,
        this, &AppContext::onLoadCurrentUserFinished);
    connect(&load_current_user_use_case, &LoadCurrentUserUseCase::loadAvatarFinished,
            this, &AppContext::onLoadAvatarFinished);

    connect(users_service.get(), &UsersService::currentUserChanged,
            this, [this](std::expected<User, Error> res) {
        if (res.has_value())
            emit currentUserChanged(res.value());
    });

    connect(&load_chats_uc, &LoadChatsForCurrentUserUseCase::requestFinished,
            this, [this](auto res) {
        emit loadingChatsFinished(res);
    });
}

AppContext::~AppContext() = default;

void AppContext::setupCurrentUserProfile() {
    is_loading_ = true;
    load_current_user_use_case.execute();
    load_chats_uc.execute(session_manager.getSession().getToken().user_id);
}

void AppContext::onLoadCurrentUserFinished(std::expected<User, Error> res) {
    if (res.has_value()) {
        session_manager.getSession().setCurrentUser(res.value());
    } else {
        User u;
        u.name = "Igor";
        u.status = "Online";

        session_manager.getSession().setCurrentUser(u);
        // throw std::runtime_error{res.error().msg};
    }

    is_loading_ = false;
    emit loadingProfileFinished();
}

void AppContext::onLoadAvatarFinished(std::expected<AvatarData, Error> res) {
    if (!res.has_value())
        return;

    auto new_av = av_provider.addImage(QString::fromStdString(res.value().user_id),
                            toQByteArray(res.value().img_data));
    emit loadingAvatarFinished(new_av);
}
