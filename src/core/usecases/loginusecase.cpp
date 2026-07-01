#include "loginusecase.h"

#include "core/ports/auth_error.h"

LoginUseCase::LoginUseCase(AuthService& s)
    : auth_service_(s)
{
    connect(&auth_service_, &AuthService::loginFinished, this, [this](AuthService::LoginResult res) {
        if (res.has_value()) {
            emit loginFinished(res.value());
        } else {
            emit loginFinished(res.transform_error([](AuthError err) {
                return LoginError{err};
            }));
        }
    });
}

void LoginUseCase::execute(const std::string &name, const std::string &password) {
    if (name.empty()) {
        emit loginFinished(std::unexpected(
            ValidationError{ValidationError::Type::EmptyLogin}
            ));
        return;
    }

    if (password.empty()) {
        emit loginFinished(std::unexpected(
            ValidationError{ValidationError::Type::EmptyPassword}
            ));
        return;
    }

    auth_service_.login(name, password);
}


