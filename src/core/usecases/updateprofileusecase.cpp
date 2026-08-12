#include "updateprofileusecase.h"

#include "core/ports/users_service.h"

UpdateProfileUseCase::UpdateProfileUseCase(UsersService* srv)
    : srv_{srv}
{
    connect(srv_, &UsersService::updateUserFinished, this,
            [this](auto res) {
        emit requestFinished(res);
    });
}

void UpdateProfileUseCase::execute(const User& u) {
    srv_->updateUser(u);
}

void UpdateProfileUseCase::execute(
    const User& u,
    const AvatarData& av)
{
    srv_->updateUser(u, av);
}
