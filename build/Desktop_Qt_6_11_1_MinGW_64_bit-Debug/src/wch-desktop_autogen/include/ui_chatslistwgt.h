/********************************************************************************
** Form generated from reading UI file 'chatslistwgt.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATSLISTWGT_H
#define UI_CHATSLISTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatsListWgt
{
public:
    QVBoxLayout *verticalLayout;
    QListView *listView;

    void setupUi(QWidget *ChatsListWgt)
    {
        if (ChatsListWgt->objectName().isEmpty())
            ChatsListWgt->setObjectName("ChatsListWgt");
        ChatsListWgt->resize(400, 300);
        verticalLayout = new QVBoxLayout(ChatsListWgt);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(ChatsListWgt);
        listView->setObjectName("listView");

        verticalLayout->addWidget(listView);


        retranslateUi(ChatsListWgt);

        QMetaObject::connectSlotsByName(ChatsListWgt);
    } // setupUi

    void retranslateUi(QWidget *ChatsListWgt)
    {
        ChatsListWgt->setWindowTitle(QCoreApplication::translate("ChatsListWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatsListWgt: public Ui_ChatsListWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATSLISTWGT_H
