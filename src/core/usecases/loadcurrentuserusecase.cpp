#include "loadcurrentuserusecase.h"

#include "core/domain/session.h"

#include <cassert>

LoadCurrentUserUseCase::LoadCurrentUserUseCase(UsersService* srv, const Session& session)
    : srv_{srv}, session_{session}
{
    assert(srv_);
    assert(!session_.getToken().value.empty());
    srv_->addOption("authorization", session_.getToken().value, "Bearer");
    connect(srv_, &UsersService::loadCurrentUserFinished, this,
            &LoadCurrentUserUseCase::onLoadCurrentUserFinished);
}

void LoadCurrentUserUseCase::execute() {
    assert(srv_);
    assert(!session_.getToken().user_id.empty());
    srv_->getUser(session_.getToken().user_id);
}

void LoadCurrentUserUseCase::onLoadCurrentUserFinished(UsersService::CurrentUserResult res) {
    emit loadCurrentUserFinished(res);
}