#include "sessionmanager.h"

SessionManager::SessionManager() {}

void SessionManager::updateUser(const User& u) {
    session_->setCurrentUser(u);
}