#include "avatarprovider.h"

#include "core/ports/users_service.h"

#include <QStandardPaths>

AvatarProvider::AvatarProvider(UsersService& srv, QObject* parent)
    : QObject(parent)
    , srv_(srv)
{
    cache_path_ = QStandardPaths::writableLocation(
        QStandardPaths::CacheLocation) + "/avatars";

    connect(&srv_, &UsersService::getAvatarFinished, this,
            &AvatarProvider::onGetAvatarFinished);
}

std::optional<QPixmap> AvatarProvider::getImage(const QString& user_id) {
    if (const auto it = memory_cache_.find(user_id); it != memory_cache_.end()) {
        return it.value();
    }

    const auto path = cache_path_ + user_id + ".png";
    QPixmap pix;
    if (pix.load(path)) {
        memory_cache_.insert(user_id, pix);
        return pix;
    }

    if (!pending_requests_.contains(user_id)) {
        pending_requests_.insert(user_id);
        srv_.requestAvatar(user_id.toStdString());
    }

    return std::nullopt;
}

void AvatarProvider::onGetAvatarFinished(std::expected<AvatarData, Error> res) {
    if (res.has_value()) {
        emit getAvatarFinished(res.value());
    }
}