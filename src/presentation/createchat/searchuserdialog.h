#pragma once

#include <QDialog>

#include <expected>

#include "core/domain/user.h"
#include "core/domain/user_summary.h"
#include "core/domain/errors.h"

class SearchUsersUseCase;
class CreateChatUseCase;
class QEvent;
class SearchUsersModel;
class AvatarProvider;

namespace Ui {
class SearchUserDialog;
}

class SearchUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchUserDialog(
        SearchUsersUseCase& suc,
        CreateChatUseCase& cuc,
        AvatarProvider* av_provider,
        QWidget *parent = nullptr);
    ~SearchUserDialog();

signals:
    void showUserProfile(const User& u, QPixmap av);
    void addUserToChat(const QString& user_id);
private slots:
    void onFindClicked();
    void onSearchFinished(std::expected<std::list<UserSummary>, Error> res);
    void onGetAvatarsFinished(const QVector<QPair<QString, QPixmap>>& res);
    void onContextMenuRequested(const QPoint& pos);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    void setupContextMenu();
    void setupLoadLabel();
    void startLoadAnim();
    void stopLoadAnim();

    void onShowProfile(const QModelIndex& idx);
    void onCreateChat(const QModelIndex& idx);
    void onAddUserToChat(const QModelIndex& idx);

    Ui::SearchUserDialog *ui;

    SearchUsersUseCase& suc_;
    CreateChatUseCase& cuc_;

    AvatarProvider* av_provider_;

    SearchUsersModel* model_;
};

