#pragma once

#include <QObject>

#include <expected>

#include "core/domain/user_summary.h"
#include "core/domain/users_search_filter.h"
#include "core/domain/errors.h"

class UsersService;

class SearchUsersUseCase : public QObject
{
    Q_OBJECT
public:
    explicit SearchUsersUseCase(UsersService* srv, QObject *parent = nullptr);

    void execute(const UsersSearchFilter& filter);
signals:
    void requestFinished(std::expected<std::list<UserSummary>, Error> res);

private:
    UsersService* srv_;
};

