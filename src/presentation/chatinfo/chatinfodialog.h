#pragma once

#include <QDialog>

#include <expected>

#include "core/domain/chat.h"
#include "core/domain/errors.h"

class UpdateChatUseCase;

namespace Ui {
class ChatInfoDialog;
}

class ChatInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatInfoDialog(UpdateChatUseCase& uc, const Chat& chat, QWidget *parent = nullptr);
    explicit ChatInfoDialog(UpdateChatUseCase& uc, QWidget *parent = nullptr);
    ~ChatInfoDialog();

    void setAvatar(QPixmap img) noexcept;
private slots:
    void onAvatarClicked();
    void onSaveClicked();
    void onChatInfoChanged(std::expected<Chat, Error> res);
private:
    void startLoadAnim();
    void stopLoadAnim();

    Ui::ChatInfoDialog *ui;

    UpdateChatUseCase& uc_;

    QString new_avatar_path_;
    Chat chat_tmp_;
};

