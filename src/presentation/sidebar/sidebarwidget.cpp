#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

#include <QAction>
#include <QPushButton>
#include <QDebug>
#include <QMovie>

SidebarWidget::SidebarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SidebarWidget)
{
    ui->setupUi(this);

    auto add_group_action = new QAction{QIcon{":/icons/icons/add.png"}, "add chat group", this};
    connect(add_group_action, &QAction::triggered, this, &SidebarWidget::onAddGroupAction);
    ui->addGroupButton->setDefaultAction(add_group_action);

    auto open_settings_action = new QAction{QIcon{":/icons/icons/settings.png"}, "settings", this};
    connect(open_settings_action, &QAction::triggered, this, &SidebarWidget::onSettingsAction);
    ui->settingButton->setDefaultAction(open_settings_action);

    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->loadingWgt->setMovie(gif);
    ui->loadingWgt->setScaledContents(true);
}

SidebarWidget::~SidebarWidget()
{
    delete ui;
}

void SidebarWidget::onAddGroupAction() {
    auto new_group_button = new QPushButton{"new group", this};
    new_group_button->setMaximumSize(ui->addGroupButton->maximumSize());
    new_group_button->setMinimumSize(ui->addGroupButton->minimumSize());
    new_group_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->groupsLayout->addWidget(new_group_button);
}

void SidebarWidget::onSettingsAction() {
    qDebug() << "open settings...";
    emit settingsOpen();
}

void SidebarWidget::startLoadingIcon() noexcept {
    ui->loadingWgt->show();
    ui->loadingWgt->movie()->start();
}

void SidebarWidget::stopLoadingIcon() noexcept {
    ui->loadingWgt->movie()->stop();
    ui->loadingWgt->hide();
}
