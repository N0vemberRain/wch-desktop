/********************************************************************************
** Form generated from reading UI file 'chatwgt.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWGT_H
#define UI_CHATWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWgt
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListView *view;
    QHBoxLayout *horizontalLayout;
    QTextEdit *msgEdit;
    QPushButton *sendButton;

    void setupUi(QWidget *ChatWgt)
    {
        if (ChatWgt->objectName().isEmpty())
            ChatWgt->setObjectName("ChatWgt");
        ChatWgt->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(ChatWgt);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        view = new QListView(ChatWgt);
        view->setObjectName("view");

        verticalLayout->addWidget(view);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        msgEdit = new QTextEdit(ChatWgt);
        msgEdit->setObjectName("msgEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(msgEdit->sizePolicy().hasHeightForWidth());
        msgEdit->setSizePolicy(sizePolicy);
        msgEdit->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(msgEdit);

        sendButton = new QPushButton(ChatWgt);
        sendButton->setObjectName("sendButton");
        sendButton->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ChatWgt);

        QMetaObject::connectSlotsByName(ChatWgt);
    } // setupUi

    void retranslateUi(QWidget *ChatWgt)
    {
        ChatWgt->setWindowTitle(QCoreApplication::translate("ChatWgt", "Form", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWgt", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWgt: public Ui_ChatWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWGT_H
