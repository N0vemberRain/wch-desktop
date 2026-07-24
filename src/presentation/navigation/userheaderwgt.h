#pragma once

#include <QWidget>

class User;

namespace Ui {
class UserHeaderWgt;
}

class UserHeaderWgt : public QWidget
{
    Q_OBJECT

public:
    explicit UserHeaderWgt(QWidget *parent = nullptr);
    ~UserHeaderWgt();

    void setUser(const User& u) noexcept;
    void setAvatar(QPixmap img);
private:
    Ui::UserHeaderWgt *ui;

};
