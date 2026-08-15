#pragma once

#include <QDialog>

#include <expected>

#include "core/domain/chat.h"
#include "core/domain/chat_participant.h"
#include "core/domain/errors.h"
#include "infrastructure/utils/avatarprovider.h"

class UpdateChatUseCase;
class LoadParticipantsUseCase;
class ChatParticipantsModel;

namespace Ui {
class ChatInfoDialog;
}

class ChatInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatInfoDialog(
        AvatarProvider* av_provider,
        UpdateChatUseCase& uuc,
        LoadParticipantsUseCase& luc,
        const Chat& chat,
        QWidget *parent = nullptr
    );
    explicit ChatInfoDialog(
        AvatarProvider* av_provider,
        UpdateChatUseCase& uuc,
        LoadParticipantsUseCase& luc,
        QWidget *parent = nullptr);
    ~ChatInfoDialog();

    void setAvatar(QPixmap img) noexcept;
private slots:
    void onAvatarClicked();
    void onSaveClicked();
    void onChatInfoChanged(std::expected<Chat, Error> res);
    void onLoadParticipantsFinished(
        std::expected<std::list<ChatParticipant>, Error> res
    );
private:
    void setup();
    void startLoadAnim();
    void stopLoadAnim();

    Ui::ChatInfoDialog *ui;

    AvatarProvider* av_provider_;
    UpdateChatUseCase& uuc_;
    LoadParticipantsUseCase& luc_;

    QString new_avatar_path_;
    Chat chat_tmp_;

    ChatParticipantsModel* model_;
};

