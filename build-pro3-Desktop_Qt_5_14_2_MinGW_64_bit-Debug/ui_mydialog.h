/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_myDialog
{
public:
    QLineEdit *nametext;
    QLineEdit *gradetext;
    QPushButton *closebtn;
    QPushButton *finishbtn;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *myDialog)
    {
        if (myDialog->objectName().isEmpty())
            myDialog->setObjectName(QString::fromUtf8("myDialog"));
        myDialog->resize(325, 255);
        nametext = new QLineEdit(myDialog);
        nametext->setObjectName(QString::fromUtf8("nametext"));
        nametext->setGeometry(QRect(109, 70, 113, 21));
        gradetext = new QLineEdit(myDialog);
        gradetext->setObjectName(QString::fromUtf8("gradetext"));
        gradetext->setGeometry(QRect(109, 110, 113, 21));
        closebtn = new QPushButton(myDialog);
        closebtn->setObjectName(QString::fromUtf8("closebtn"));
        closebtn->setGeometry(QRect(189, 160, 81, 28));
        finishbtn = new QPushButton(myDialog);
        finishbtn->setObjectName(QString::fromUtf8("finishbtn"));
        finishbtn->setGeometry(QRect(59, 160, 93, 28));
        label = new QLabel(myDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 70, 71, 20));
        label_2 = new QLabel(myDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 110, 71, 20));

        retranslateUi(myDialog);

        QMetaObject::connectSlotsByName(myDialog);
    } // setupUi

    void retranslateUi(QDialog *myDialog)
    {
        myDialog->setWindowTitle(QCoreApplication::translate("myDialog", "Dialog", nullptr));
        closebtn->setText(QCoreApplication::translate("myDialog", "\345\205\263\351\227\255", nullptr));
        finishbtn->setText(QCoreApplication::translate("myDialog", "\350\276\223\345\205\245\345\256\214\346\210\220", nullptr));
        label->setText(QCoreApplication::translate("myDialog", "\350\257\276\347\250\213\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("myDialog", "\346\210\220\347\273\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myDialog: public Ui_myDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
