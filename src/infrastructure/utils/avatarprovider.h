#pragma once

#include <QObject>
#include <QPixmap>
#include <QHash>
#include <QSet>

#include <string>
#include <expected>

#include "core/domain/types.h"
#include "core/domain/errors.h"

class UsersService;

class AvatarProvider : public QObject
{
    Q_OBJECT
public:
    explicit AvatarProvider(UsersService& srv, QObject* parent = nullptr);

    const QPixmap& getImage(const std::string& user_id) const;
    std::optional<QPixmap> getImage(const QString& user_id);

private slots:
    void onGetAvatarFinished(std::expected<AvatarData, Error> res);

signals:
    void getAvatarFinished(const AvatarData& data);

private:
    UsersService& srv_;

    QHash<QString, QPixmap> memory_cache_;
    QSet<QString> pending_requests_;

    QString cache_path_;
};
