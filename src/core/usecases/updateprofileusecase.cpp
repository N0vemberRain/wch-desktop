#include "updateprofileusecase.h"

#include "core/ports/users_service.h"

UpdateProfileUseCase::UpdateProfileUseCase(UsersService* srv)
    : srv_{srv}
{
    connect(srv_, &UsersService::currentUserChanged, this,
            [this](std::expected<User, Error> res) {
        emit requestFinished(res);
    });
}

void UpdateProfileUseCase::execute(const User& u) {
    srv_->updateUser(u);
}
