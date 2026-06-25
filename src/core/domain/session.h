#pragma once

#include <memory>
#include <cassert>

#include "user.h"

class Session
{
public:
    Session();

    void setCurrentUser(std::unique_ptr<User> u) noexcept {
        current_user_.reset(u.release());
    }
    const User& getCurrentUser() const noexcept {
        assert(current_user_);
        return *current_user_;
    }
    const std::string& getCurrentUserID() const noexcept {
        assert(current_user_);
        return current_user_->id;
    }
private:
    std::unique_ptr<User> current_user_;
};
