#pragma once

#include <string>
#include <expected>

#include "core/ports/authservice.h"
#include "login_error.h"

using LoginResult = std::expected<User, LoginError>;

class LoginUseCase
{
public:
    explicit LoginUseCase(AuthService& s);

    LoginResult execute(const std::string& name,
                                  const std::string& password);

private:
    AuthService& auth_service_;
};