#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>

class User;

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = nullptr);
    ~ProfileDialog();

    void setUser(const User& u) noexcept;

signals:
    void avatarChanged(const QString& filename);
private slots:
    void onAvatarClicked();
private:
    Ui::ProfileDialog *ui;
};

#endif // PROFILEDIALOG_H
