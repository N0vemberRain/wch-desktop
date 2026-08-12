#pragma once

#include <memory>
#include <cassert>

#include "core/domain/session.h"

class SessionManager
{
public:
    SessionManager();

    bool hasSession() const noexcept {
        return session_ != nullptr;
    }
    auto getSessionPtr() noexcept {
        return session_;
    }
    const Session& getSession() const noexcept {
        assert(session_);
        return *session_;
    }
    Session& getSession() noexcept {
        assert(session_);
        return *session_;
    }

    void setSession(std::shared_ptr<Session> s) noexcept {
        session_ = s;
    }

    void clear() noexcept {
        session_.reset();
    }

    void updateUser(const User& u);
private:
    std::shared_ptr<Session> session_;
};

