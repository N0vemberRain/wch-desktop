#include "loginusecase.h"

LoginUseCase::LoginUseCase(AuthService& s)
    : auth_service_(s)
{

}

LoginResult LoginUseCase::execute(const std::string &name, const std::string &password) {
    if (name.empty()) {
        return std::unexpected(
            ValidationError{ValidationError::Type::EmptyLogin}
        );
    }

    if (password.empty()) {
        return std::unexpected(
            ValidationError{ValidationError::Type::EmptyPassword}
        );
    }

    return auth_service_.login(name, password)
        .transform_error([](AuthError e) {
            return LoginError{e};
        });
}
