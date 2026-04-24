#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <memory>
#include <tuple>
#include <string>

#include "core/domain/user.h"

using LoginResult = std::tuple<std::unique_ptr<User>, std::string>;

class AuthService {
public:
    virtual ~AuthService() = default;

    virtual LoginResult login(const std::string& name,
                              const std::string& password) = 0;
};

#endif // AUTHSERVICE_H
