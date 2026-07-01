#pragma once

#include "user.h"
#include "token.h"

class Session
{
public:
    Session();

    void setCurrentUser(User u) noexcept {
        current_user_ = u;
    }
    const User& getCurrentUser() const noexcept {
        return current_user_;
    }
    const std::string& getCurrentUserID() const noexcept {
        return current_user_.id;
    }

    void setToken(Token t) noexcept {
        token_ = t;
    }
    const Token& getToken() const noexcept {
        return token_;
    }
private:
    User current_user_;
    Token token_;
};
