#ifndef LOGINUSECASE_H
#define LOGINUSECASE_H

#include <string>
#include <memory>

#include "core/domain/user.h"
#include "core/ports/authservice.h"

class LoginUseCase
{
public:
    explicit LoginUseCase(AuthService& s);

    LoginResult execute(const std::string& name,
                                  const std::string& password);

private:
    AuthService& auth_service_;
};

#endif // LOGINUSECASE_H
