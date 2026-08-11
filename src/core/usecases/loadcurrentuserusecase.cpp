#include "loadcurrentuserusecase.h"

#include "core/domain/session.h"

LoadCurrentUserUseCase::LoadCurrentUserUseCase(UsersService* srv)
    : srv_{srv}
{
    assert(srv_);
    // assert(!session_->getToken().value.empty());
    connect(srv_, &UsersService::loadCurrentUserFinished, this,
            &LoadCurrentUserUseCase::onLoadCurrentUserFinished);
    connect(srv_, &UsersService::getAvatarFinished, this,
            &LoadCurrentUserUseCase::onGetAvatarFinished);
}

void LoadCurrentUserUseCase::setSession(std::shared_ptr<Session> s_ptr) noexcept {
    assert(s_ptr);
    session_ = s_ptr;
    srv_->addOption("authorization", session_->getToken().value, "Bearer");
}

void LoadCurrentUserUseCase::execute() {
    assert(srv_);
    assert(session_);
    assert(!session_->getToken().user_id.empty());
    srv_->getUser(session_->getToken().user_id);
    // srv_->requestAvatar(session_.getToken().user_id);
}

void LoadCurrentUserUseCase::onLoadCurrentUserFinished(UsersService::CurrentUserResult res) {
    assert(srv_);
    assert(session_);
    emit loadCurrentUserFinished(res);

    srv_->requestAvatar(session_->getToken().user_id);
}

void LoadCurrentUserUseCase::onGetAvatarFinished(std::expected<AvatarData, Error> res) {
    emit loadAvatarFinished(res);
}