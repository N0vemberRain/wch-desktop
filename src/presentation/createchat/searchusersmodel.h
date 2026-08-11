#pragma once

#include <QAbstractListModel>
#include <QPixmap>

struct UserItem {
    QString id;
    QString name;
    QString email;
    QPixmap avatar;
};

class SearchUsersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ID = Qt::UserRole + 1,
        NameRole,
        EmailRole,
        AvatarRole,
    };

    explicit SearchUsersModel(QObject *parent = nullptr);
    ~SearchUsersModel() = default;

    void addUser(const UserItem& item) noexcept;
    void addAvatarForUser(const QString& user_id, QPixmap img) noexcept;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void clear() noexcept;
protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<UserItem> users_;
};

