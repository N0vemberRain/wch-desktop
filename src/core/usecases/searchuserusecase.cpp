#include "searchuserusecase.h"

#include "core/ports/users_service.h"

SearchUserUseCase::SearchUserUseCase(UsersService* srv, QObject *parent)
    : QObject{parent}
{}
