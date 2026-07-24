#pragma once

#include <QDialog>

#include <expected>

#include "core/domain/errors.h"
#include "core/domain/user.h"

class UpdateProfileUseCase;

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(UpdateProfileUseCase& uc, QWidget *parent = nullptr);
    ~ProfileDialog();

    void setUser(const User& u) noexcept;
    void setAvatar(QPixmap img) noexcept;

signals:
    void avatarChanged(const QString& filename);
private slots:
    void onAvatarClicked();
    void onSaveClicked();
    void onProfileChanged(std::expected<User, Error> res);
private:
    void startLoadAnim();
    void stopLoadAnim();

    Ui::ProfileDialog *ui;

    UpdateProfileUseCase& uc_;


    QString new_avatar_path_;
};

