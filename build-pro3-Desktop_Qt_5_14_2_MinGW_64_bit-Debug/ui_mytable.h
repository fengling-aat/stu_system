/********************************************************************************
** Form generated from reading UI file 'mytable.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTABLE_H
#define UI_MYTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mytable
{
public:

    void setupUi(QWidget *mytable)
    {
        if (mytable->objectName().isEmpty())
            mytable->setObjectName(QString::fromUtf8("mytable"));
        mytable->resize(400, 300);

        retranslateUi(mytable);

        QMetaObject::connectSlotsByName(mytable);
    } // setupUi

    void retranslateUi(QWidget *mytable)
    {
        mytable->setWindowTitle(QCoreApplication::translate("mytable", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mytable: public Ui_mytable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTABLE_H
