#pragma once

#include <QString>

#include "core/usecases/login_error.h"

inline QString toQString(const LoginError& err) {
    return std::visit([](auto&& e) -> QString {
        using ErrType = std::decay_t<decltype(e)>;

        if constexpr (std::is_same_v<ErrType, ValidationError>) {
            switch (e.type) {
            case ValidationError::Type::EmptyLogin:
                return "Login is empty";
            case ValidationError::Type::EmptyPassword:
                return "Password is empty";
            }
        }

        if constexpr (std::is_same_v<ErrType, AuthError>) {
            switch (e) {
            case AuthError::InvalidCredentials:
                return "Invalid login or password";
            case AuthError::AccountLocked:
                return "Account is locked";
            case AuthError::NetworkError:
                return "Network error. Try again.";
            }
        }

        return "unknown error";
    }, err);
}