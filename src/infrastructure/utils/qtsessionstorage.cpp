#include "qtsessionstorage.h"

#include "utils.h"

QtSessionStorage::QtSessionStorage()
    : settings_{/*"IgorCompany", "wch-desktop"*/}
{}

std::optional<Session> QtSessionStorage::load() {
    const auto token = settings_.value("session/token").toString();
    if (token.isEmpty()) {
        return std::nullopt;
    }

    Session s;
    Token t;
    t.value = token.toStdString();

    t.user_id = settings_.value("session/user_id")
                    .toString()
                    .toStdString();

    t.expires_at = fromQString(settings_.value("session/expires_at").toString());

    s.setToken(t);

    return s;
}

void QtSessionStorage::save(const Session& s) {
    settings_.setValue("session/token", QString::fromStdString(s.getToken().value));
    settings_.setValue("session/user_id", QString::fromStdString(s.getToken().user_id));
    settings_.setValue("session/expires_at", toQString(s.getToken().expires_at));

    settings_.sync();
}

void QtSessionStorage::clear() {
    settings_.remove("session");
    settings_.sync();
}