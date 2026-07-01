#pragma once

#include <optional>

#include "core/domain/session.h"

class SessionStorage {
public:
    virtual ~SessionStorage() = default;

    virtual std::optional<Session> load() = 0;
    virtual void save(const Session& s) = 0;
    virtual void clear() = 0;
};
