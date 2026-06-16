#ifndef SESSION_H
#define SESSION_H

#include <memory>

#include "user.h"

class Session
{
public:
    Session();

    void setCurrentUser(std::unique_ptr<User> u) noexcept {
        current_user_.reset(u.release());
    }
    const User& getCurrentUser() const noexcept {
        return *current_user_;
    }
    const std::string& getCurrentUserID() const noexcept {
        return current_user_->id;
    }
private:
    std::unique_ptr<User> current_user_;
};

#endif // SESSION_H
