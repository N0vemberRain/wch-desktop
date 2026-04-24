#ifndef QTAUTHSERVICE_H
#define QTAUTHSERVICE_H

#include <memory>
#include <string>

#include "core/ports/authservice.h"

class QtAuthService : public AuthService
{
public:
    QtAuthService();

    LoginResult login(const std::string& name,
                      const std::string& password) override;
};

#endif // QTAUTHSERVICE_H
