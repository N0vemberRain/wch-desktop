#pragma once

#include <string>
#include <expected>

#include "core/domain/user.h"
#include "auth_error.h"


class AuthService {
protected:
    using LoginResult = std::expected<User, AuthError>;
public:
    virtual ~AuthService() = default;

    virtual LoginResult login(const std::string& name,
                              const std::string& password) = 0;
};
