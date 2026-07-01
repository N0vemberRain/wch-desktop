#pragma once

#include <optional>
#include <cassert>

#include "core/domain/session.h"

class SessionManager
{
public:
    SessionManager();

    bool hasSession() const noexcept {
        return session_.has_value();
    }
    const Session& getSession() const noexcept {
        assert(session_.has_value());
        return session_.value();
    }

    void setSession(Session s) noexcept {
        session_ = std::move(s);
    }

    void clear() noexcept {
        session_.reset();
    }
private:
    std::optional<Session> session_;
};

