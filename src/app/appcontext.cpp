#include "appcontext.h"

#include "core/ports/authservice.h"
#include "core/ports/users_service.h"
#include "core/ports/msgservice.h"


AppContext::AppContext(std::unique_ptr<AuthService> as,
                       std::unique_ptr<UsersService> us,
                       std::unique_ptr<MessageService> ms,
                       std::unique_ptr<SessionStorage> ses_storage,
                       std::unique_ptr<LoginUseCase> login_use_case,
                       SessionManager&& sm)
    :
    auth_service{std::move(as)},
    users_service{std::move(us)},
    msgs_service{std::move(ms)},
    session_storage{std::move(ses_storage)},
    session_manager{std::move(sm)},
    login_use_case{std::move(login_use_case)},
    load_current_user_use_case{users_service.get(), session_manager.getSession()},
    send_msgs_use_case{msgs_service.get(), session_manager.getSession()}
{
    if (!session_manager.hasSession()) {
        throw std::runtime_error{"session has to be initialized before AppContext"};
    }

    connect(&load_current_user_use_case, &LoadCurrentUserUseCase::loadCurrentUserFinished,
        this, &AppContext::onLoadCurrentUserFinished);
}

void AppContext::setupCurrentUserProfile() {
    load_current_user_use_case.execute();
}

void AppContext::onLoadCurrentUserFinished(std::expected<User, Error> res) {
    if (res.has_value()) {
        session_manager.getSession().setCurrentUser(res.value());
    } else {
        throw std::runtime_error{res.error().msg};
    }
}
