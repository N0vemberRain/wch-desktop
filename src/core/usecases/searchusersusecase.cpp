#include "searchusersusecase.h"

#include "core/ports/users_service.h"



SearchUsersUseCase::SearchUsersUseCase(UsersService* srv, QObject *parent)
    : QObject{parent}
    , srv_(srv)
{
    connect(srv_, &UsersService::searchUsersFinished, [this](auto res) {
        emit requestFinished(res);
    });
}

void SearchUsersUseCase::execute(const UsersSearchFilter& filter) {
    srv_->searchUsers(filter);
}