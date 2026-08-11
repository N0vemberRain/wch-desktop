#pragma once

#include <QWidget>

namespace Ui {
class SidebarWidget;
}

class SidebarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SidebarWidget(QWidget *parent = nullptr);
    ~SidebarWidget();

    void startLoadingIcon() noexcept;
    void stopLoadingIcon() noexcept;
private slots:
    void onAddGroupChatAction();
    void onSettingsAction();

signals:
    void settingsOpen();
    void createNewChat();

    void logoutClicked();

private:
    Ui::SidebarWidget *ui;
};

