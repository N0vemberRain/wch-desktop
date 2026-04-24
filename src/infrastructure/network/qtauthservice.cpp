#include "qtauthservice.h"

QtAuthService::QtAuthService()
{

}

LoginResult QtAuthService::login(const std::string &name, const std::string &password) {
    if (name == "test" && password == "123") {
        auto u = std::make_unique<User>();
        u->id = "123";
        u->name = "test";

        return {std::move(u), ""};
    }

    return {nullptr, "Empty credentials"};
}
