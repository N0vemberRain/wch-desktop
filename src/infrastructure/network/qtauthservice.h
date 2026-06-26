#pragma once

#include <string>

#include "core/ports/authservice.h"

class QtAuthService : public AuthService
{
public:
    QtAuthService();

    AuthService::LoginResult login(const std::string& name,
                      const std::string& password) override;
};
