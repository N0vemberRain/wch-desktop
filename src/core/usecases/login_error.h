#pragma once

#include <variant>

#include "core/ports/auth_error.h"

struct ValidationError {
    enum class Type {
        EmptyLogin,
        EmptyPassword
    };

    Type type;
};

using LoginError = std::variant<ValidationError, AuthError>;