#pragma once

#include <QObject>
#include <QPixmap>
#include <QHash>
#include <QSet>

#include <expected>

#include "core/domain/types.h"
#include "core/domain/errors.h"

class UsersService;

class AvatarProvider : public QObject
{
    Q_OBJECT
public:
    explicit AvatarProvider(UsersService& srv, QObject* parent = nullptr);

    // const QPixmap& getImage(const std::string& user_id) const;
    std::optional<QPixmap> getImage(const QString& user_id);
    QVector<QPair<QString, QPixmap>> getImages(const QStringList& ids);

    void updateImage(const QString& user_id, const QString& av_url);
    QPixmap addImage(const QString& user_id, const QByteArray& img_data);
private slots:
    void onGetAvatarFinished(std::expected<AvatarData, Error> res);
    void onGetAvatarsFinished(std::expected<std::list<AvatarData>, Error> res);
signals:
    void getAvatarFinished(const AvatarData& data);
    // void getAvatarsFinished(const std::list<AvatarData>& avs);
    void getAvatarsFinished(const QVector<QPair<QString, QPixmap>>& res);

private:
    void save(const QString& user_id, QPixmap pix);

    UsersService& srv_;

    QHash<QString, QPixmap> memory_cache_;
    QSet<QString> pending_requests_;

    QString cache_path_;
};
