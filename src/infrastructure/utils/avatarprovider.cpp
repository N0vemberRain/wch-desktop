#include "avatarprovider.h"

#include "core/ports/users_service.h"
#include "utils.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>

AvatarProvider::AvatarProvider(UsersService& srv, QObject* parent)
    : QObject(parent)
    , srv_(srv)
{
    cache_path_ = QStandardPaths::writableLocation(
        QStandardPaths::CacheLocation) + "/avatars";

    QDir cache_dir{cache_path_};
    if (!cache_dir.exists()) {
        if (!cache_dir.mkpath(".")) {
            throw std::runtime_error{
                "AvatarProvider: Can't create cache directory"
            };
        }
    }

    connect(&srv_, &UsersService::getAvatarFinished, this,
            &AvatarProvider::onGetAvatarFinished);
    connect(&srv_, &UsersService::getAvatarsFinished, this,
            &AvatarProvider::onGetAvatarsFinished);
}

std::optional<QPixmap> AvatarProvider::getImage(const QString& user_id) {
    // if (const auto it = memory_cache_.find(user_id); it != memory_cache_.end()) {
    //     return it.value();
    // }

    // const auto path = cache_path_ + "/" + user_id + ".png";
    // QPixmap pix;
    // if (pix.load(path)) {
    //     memory_cache_.insert(user_id, pix);
    //     return pix;
    // }

    if (!pending_requests_.contains(user_id)) {
        pending_requests_.insert(user_id);
        srv_.requestAvatar(user_id.toStdString());
    }

    return std::nullopt;
}

QVector<QPair<QString, QPixmap>> AvatarProvider::getImages(const QStringList& qids) {
    QVector<QPair<QString, QPixmap>> res;
    std::list<std::string> ids;
    foreach (const auto& id, qids) {
        // if (const auto it = memory_cache_.find(id);
        //     it != memory_cache_.end()) {
        //     res.append({id, it.value()});

        //     continue;
        // }

        // const auto path = cache_path_ + "/" + id + ".png";
        // QPixmap pix;
        // if (pix.load(path)) {
        //     memory_cache_.insert(id, pix);
        //     res.append({id, pix});

        //     continue;
        // }

        ids.push_back(id.toStdString());
    }

    if (!ids.empty())
        srv_.requestAvatars(ids);

    return res;
}

void AvatarProvider::onGetAvatarFinished(std::expected<AvatarData, Error> res) {
    if (res.has_value()) {
        QPixmap pix;
        pix.loadFromData(toQByteArray(res.value().img_data));
        memory_cache_.insert(QString::fromStdString(res.value().user_id), pix);
        pix.save(cache_path_ + "/" + QString::fromStdString(res.value().user_id) + ".png", "PNG");

        emit getAvatarFinished(res.value());
    }
}

void AvatarProvider::onGetAvatarsFinished(
    std::expected<std::list<AvatarData>, Error> res
) {
    if (!res.has_value())
        return;

    QVector<QPair<QString, QPixmap>> avs;
    for (const auto& av_data : res.value()) {
        QPixmap pix;
        pix.loadFromData(toQByteArray(av_data.img_data));
        memory_cache_.insert(
            QString::fromStdString(av_data.user_id), pix
        );
        pix.save(
            cache_path_ +
            "/" +
            QString::fromStdString(av_data.user_id) +
            ".png",
            "PNG"
        );

        avs.append({QString::fromStdString(av_data.user_id), pix});
    }

    emit getAvatarsFinished(avs);
}
void AvatarProvider::updateImage(const QString& user_id, const QString& av_url) {
    QPixmap new_av;
    if(!new_av.load(av_url)) {
        throw std::runtime_error{
            "AvatarProvider:updateImage: can't load image from file " +
            av_url.toStdString()};
    }

    memory_cache_[user_id] = new_av;
    save(user_id, new_av);
}

QPixmap AvatarProvider::addImage(const QString& user_id, const QByteArray& img_data) {
    QPixmap pix;
    if (!pix.loadFromData(img_data, "PNG")) {
        throw std::runtime_error{"AvatarProvider::addImage: can't crate a new avatar from data"};
    }

    memory_cache_[user_id] = pix;
    save(user_id, pix);

    return pix;
}

QPixmap AvatarProvider::addImage(const AvatarData& data) {
    if (data.img_data.empty()) {
        throw std::runtime_error{"AvatarProvider:addImage: image data is empty"};
    }
    if (data.user_id.empty()) {
        throw std::runtime_error{"AvatarProvider:addImage: user id is empty"};
    }
    if (data.mime_type.empty()) {
        throw std::runtime_error{"AvatarProvider:addImage: mime type is empty"};
    }
    QPixmap pix;
    if (!pix.loadFromData(
            toQByteArray(data.img_data),
            data.mime_type.data()
    )) {
        throw std::runtime_error{"AvatarProvider::addImage: can't crate a new avatar from data"};
    }

    QString qid = QString::fromStdString(data.user_id);
    memory_cache_[qid] = pix;
    save(qid, pix);

    return pix;
}

QString AvatarProvider::addAvatarForUser(const AvatarData& av) {
    QPixmap pix;
    if (!pix.loadFromData(toQByteArray(av.img_data))) {
        throw std::runtime_error{"AvatarProvider::addImage: can't crate a new avatar from data"};
    }

    const auto qid = QString::fromStdString(av.user_id);
    auto key = save(qid, pix);
    memory_cache_[qid] = pix;

    return key;
}

QString AvatarProvider::save(const QString& user_id, QPixmap pix) {
    const auto filename = cache_path_ + "/" + user_id + ".png";
    if (!pix.save(filename, "PNG")) {
        throw std::runtime_error{
            "AvatartProvider:updateImage: can't save image on disk " +
            filename.toStdString()};
    }

    return filename;
}