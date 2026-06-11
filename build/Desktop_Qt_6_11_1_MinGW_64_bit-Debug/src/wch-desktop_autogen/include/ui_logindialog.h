/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *errorLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(254, 140);
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        loginLineEdit = new QLineEdit(LoginDialog);
        loginLineEdit->setObjectName("loginLineEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, loginLineEdit);

        passwordLineEdit = new QLineEdit(LoginDialog);
        passwordLineEdit->setObjectName("passwordLineEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, passwordLineEdit);

        label = new QLabel(LoginDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);


        verticalLayout->addLayout(formLayout);

        errorLabel = new QLabel(LoginDialog);
        errorLabel->setObjectName("errorLabel");

        verticalLayout->addWidget(errorLabel);

        buttonBox = new QDialogButtonBox(LoginDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LoginDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, LoginDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, LoginDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        loginLineEdit->setText(QCoreApplication::translate("LoginDialog", "test", nullptr));
        passwordLineEdit->setText(QCoreApplication::translate("LoginDialog", "123", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        errorLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
