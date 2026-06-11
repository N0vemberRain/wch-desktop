/********************************************************************************
** Form generated from reading UI file 'sidebarwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBARWIDGET_H
#define UI_SIDEBARWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SidebarWidget
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *settingButton;
    QVBoxLayout *groupsLayout;
    QToolButton *addGroupButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SidebarWidget)
    {
        if (SidebarWidget->objectName().isEmpty())
            SidebarWidget->setObjectName("SidebarWidget");
        SidebarWidget->resize(78, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SidebarWidget->sizePolicy().hasHeightForWidth());
        SidebarWidget->setSizePolicy(sizePolicy);
        SidebarWidget->setMaximumSize(QSize(274, 16777215));
        verticalLayout = new QVBoxLayout(SidebarWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        settingButton = new QToolButton(SidebarWidget);
        settingButton->setObjectName("settingButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(settingButton->sizePolicy().hasHeightForWidth());
        settingButton->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingButton->setIcon(icon);
        settingButton->setIconSize(QSize(70, 70));

        verticalLayout->addWidget(settingButton);

        groupsLayout = new QVBoxLayout();
        groupsLayout->setObjectName("groupsLayout");

        verticalLayout->addLayout(groupsLayout);

        addGroupButton = new QToolButton(SidebarWidget);
        addGroupButton->setObjectName("addGroupButton");
        sizePolicy1.setHeightForWidth(addGroupButton->sizePolicy().hasHeightForWidth());
        addGroupButton->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addGroupButton->setIcon(icon1);
        addGroupButton->setIconSize(QSize(70, 70));

        verticalLayout->addWidget(addGroupButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SidebarWidget);

        QMetaObject::connectSlotsByName(SidebarWidget);
    } // setupUi

    void retranslateUi(QWidget *SidebarWidget)
    {
        SidebarWidget->setWindowTitle(QCoreApplication::translate("SidebarWidget", "Form", nullptr));
        settingButton->setText(QCoreApplication::translate("SidebarWidget", "...", nullptr));
        addGroupButton->setText(QCoreApplication::translate("SidebarWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SidebarWidget: public Ui_SidebarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBARWIDGET_H
