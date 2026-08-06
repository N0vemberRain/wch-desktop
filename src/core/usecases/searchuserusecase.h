#pragma once

#include <QObject>

class UsersService;

class SearchUserUseCase : public QObject
{
    Q_OBJECT
public:
    explicit SearchUserUseCase(UsersService* srv, QObject *parent = nullptr);

    void execute();
signals:

private:
    UsersService* srv_;
};

