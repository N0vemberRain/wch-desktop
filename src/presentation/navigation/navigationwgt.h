#pragma once

#include <QFrame>

class QPushButton;
class UserHeaderWgt;
class User;
class AvatarData;

class NavigationWgt : public QFrame
{
    Q_OBJECT
public:
    explicit NavigationWgt(QWidget* parent = nullptr);

    void setUser(const User& u) noexcept;

public slots:
    void setAvatar(QPixmap img) noexcept;
signals:
    void profileClicked();
    void settingsClicked();
    void logoutClicked();
private:
    QPushButton* profile_button_;
    QPushButton* settings_button_;
    QPushButton* logout_button_;

    UserHeaderWgt* user_wgt_;
};
