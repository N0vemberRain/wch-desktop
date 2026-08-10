#pragma once

#include <QDialog>

#include <expected>

#include "core/domain/user_summary.h"
#include "core/domain/errors.h"

class SearchUsersUseCase;
class QEvent;
class SearchUsersModel;

namespace Ui {
class SearchUserDialog;
}

class SearchUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchUserDialog(SearchUsersUseCase& uc, QWidget *parent = nullptr);
    ~SearchUserDialog();

private slots:
    void onFindClicked();
    void onSearchFinished(std::expected<std::list<UserSummary>, Error> res);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    void setupLoadLabel();
    void startLoadAnim();
    void stopLoadAnim();

    Ui::SearchUserDialog *ui;

    SearchUsersUseCase& uc_;

    SearchUsersModel* model_;
};

