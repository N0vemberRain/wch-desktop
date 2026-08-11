#pragma once

#include <QDialog>

#include <expected>

#include "core/domain/user_summary.h"
#include "core/domain/errors.h"

class SearchUsersUseCase;
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
        SearchUsersUseCase& uc,
        AvatarProvider* av_provider,
        QWidget *parent = nullptr);
    ~SearchUserDialog();

private slots:
    void onFindClicked();
    void onSearchFinished(std::expected<std::list<UserSummary>, Error> res);
    void onGetAvatarsFinished(const QVector<QPair<QString, QPixmap>>& res);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    void setupLoadLabel();
    void startLoadAnim();
    void stopLoadAnim();

    Ui::SearchUserDialog *ui;

    SearchUsersUseCase& uc_;

    AvatarProvider* av_provider_;

    SearchUsersModel* model_;
};

