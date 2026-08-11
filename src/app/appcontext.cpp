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
    load_current_user_use_case{users_service.get()/*, session_manager.getSession()*/},
    send_msgs_use_case{msgs_service.get()/*, session_manager.getSession()*/},
    update_profile_uc{users_service.get()},
    search_users_uc{users_service.get()},
    load_chats_uc{chats_service.get()},
    update_chat_uc{chats_service.get()},
    create_chat_uc{chats_service.get()},
    av_provider{std::make_unique<AvatarProvider>(*users_service.get())}
{
    // if (!session_manager.hasSession()) {
    //     throw std::runtime_error{"session has to be initialized before AppContext"};
    // }

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
            this, &AppContext::onLoadChatsFinished);
    connect(&load_chats_uc, &LoadChatsForCurrentUserUseCase::requestAvatarsFinished,
            this, [this](std::expected<std::vector<AvatarData>, Error> res) {
        if (!res.has_value()) {
            return;
        }

        QHash<QString, QPixmap> avs;
        for (const auto& av : res.value()) {
            auto pix = av_provider->addImage(
                QString::fromStdString(av.user_id),
                toQByteArray(av.img_data));
            avs.insert(QString::fromStdString(av.user_id), pix);
        }

        emit loadingAvatarsForChatsFinished(avs);
    });


    connect(&update_chat_uc, &UpdateChatUseCase::requestFinished,
            this, &AppContext::onUpdateChatFinished);
    connect(&create_chat_uc, &CreateChatUseCase::requestFinished,
            this, &AppContext::onCreateChatFinished);
}

AppContext::~AppContext() = default;

void AppContext::loadSession() {
    auto session = session_storage->load();
    if (session.has_value()) {
        auto s_ptr = std::make_shared<Session>(session.value());
        session_manager.setSession(s_ptr);
        setupSession();
    }
}

void AppContext::setupSession() {
    load_current_user_use_case.setSession(session_manager.getSessionPtr());
    send_msgs_use_case.setSession(session_manager.getSessionPtr());
        chats_service->addOption("authorization",
                 session_manager.getSession().getToken().value,
                 "Bearer");

    setupCurrentUserProfile();
}

const User& AppContext::getCurrentUser() const noexcept {
    return session_manager.getSession().getCurrentUser();
}

const UserID& AppContext::getCurrentUserID() const noexcept {
    return session_manager.getSession().getCurrentUserID();
}

const Token& AppContext::getToken() const noexcept {
    return session_manager.getSession().getToken();
}

AvatarProvider* AppContext::getAvatarProvider() const noexcept {
    return av_provider.get();
}

const SendMessageUseCase& AppContext::getSendMessageUC() const noexcept {
    return send_msgs_use_case;
}

UpdateProfileUseCase& AppContext::getUpdateUserUC() noexcept {
    return update_profile_uc;
}

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

    auto new_av = av_provider->addImage(QString::fromStdString(res.value().user_id),
                            toQByteArray(res.value().img_data));
    emit loadingAvatarFinished(new_av);
}

void AppContext::onLoadChatsFinished(std::expected<std::list<Chat>, Error> res) {
    emit loadingChatsFinished(res);

    if (!res.has_value()) {
        return;
    }


}

void AppContext::onUpdateChatFinished(std::expected<Chat, Error> res, AvatarData av) {
    if (!res.has_value()) {
        return;
    }

    if (av.img_data.size() != 0) {
        auto new_img = av_provider->addImage(
            QString::fromStdString(av.user_id),
            toQByteArray(av.img_data));

        emit updateChatFinished(res.value(), new_img);
        return;
    }

    emit updateChatFinished(res.value(), QPixmap{});
}


void AppContext::onCreateChatFinished(
    std::expected<std::pair<Chat, std::optional<AvatarData>>, Error> res
) {
    if (!res.has_value()) {
        return;
    }

    const auto [chat, av_opt] = res.value();
    if (av_opt.has_value()) {
        auto pix = av_provider->addImage(
            QString::fromStdString(chat.id),
            toQByteArray(av_opt->img_data)
        );

        emit createChatFinished(chat, pix);
    } else {
        emit createChatFinished(chat, std::nullopt);
    }
}

void AppContext::clearSession() {
    session_storage->clear();
}