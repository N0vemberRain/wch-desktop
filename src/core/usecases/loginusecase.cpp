#include "loginusecase.h"

LoginUseCase::LoginUseCase(AuthService& s)
    : auth_service_(s)
{

}

LoginResult LoginUseCase::execute(const std::string &name, const std::string &password) {
    if (name.empty() || password.empty()) {
        return {nullptr, "Empty credentials"};
    }

    return auth_service_.login(name, password);
}
