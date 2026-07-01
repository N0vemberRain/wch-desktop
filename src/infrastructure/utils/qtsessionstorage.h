#pragma once

#include "core/ports/session_storage.h"

#include <QSettings>

class QtSessionStorage : public SessionStorage
{
public:
    QtSessionStorage();
    ~QtSessionStorage() = default;

    std::optional<Session> load() override;
    void save(const Session& s) override;
    void clear() override;
private:
    QSettings settings_;
};

