#include "qtauthservice.h"

QtAuthService::QtAuthService()
{

}

AuthService::LoginResult QtAuthService::login(const std::string &name, const std::string &password) {
    if (name == "test" && password == "123") {
        User u;
        u.id = "123";
        u.name = "test";

        return u;
    }

    return std::unexpected(AuthError::InvalidCredentials);
}
