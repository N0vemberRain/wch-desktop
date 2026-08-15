#pragma once

#include <QAbstractListModel>
#include <QPixmap>

struct ParticipantItem {
    ParticipantItem(
        const std::string& user_id,
        const std::string& name,
        QPixmap av
    )
        : user_id{QString::fromStdString(user_id)}
        , name{QString::fromStdString(name)}
        , avatar{av}
    {}
    QString user_id;
    QString name;
    QPixmap avatar;
};

class ChatParticipantsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        UserID = Qt::UserRole + 1,
        Name,
        Avatar,
    };

    explicit ChatParticipantsModel(QObject *parent = nullptr);
    ~ChatParticipantsModel() = default;


    void addUser(const ParticipantItem& item) noexcept;
    void addAvatarForUser(const QString& user_id, QPixmap img) noexcept;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<ParticipantItem> users_;
};

