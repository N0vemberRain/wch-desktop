#pragma once

#include <string>

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