#pragma once

#include "user.h"

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
private:
    User current_user_;
};
