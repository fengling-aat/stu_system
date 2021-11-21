/********************************************************************************
** Form generated from reading UI file 'system.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_System
{
public:
    QWidget *centralwidget;
    QTabWidget *mytab;
    QWidget *main;
    QPushButton *savebtn;
    QPushButton *view_all_stu;
    QLineEdit *id_search;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *name_search;
    QPushButton *freshbtn;
    QWidget *student;
    QPushButton *view_stu_grd;
    QPushButton *add_stu;
    QPushButton *adjustbtn;
    QPushButton *del_stu;
    QLineEdit *id_mhss;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *name_mhss;
    QWidget *tab;
    QPushButton *view_grade;
    QPushButton *view_all_crs;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *System)
    {
        if (System->objectName().isEmpty())
            System->setObjectName(QString::fromUtf8("System"));
        System->resize(330, 510);
        centralwidget = new QWidget(System);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mytab = new QTabWidget(centralwidget);
        mytab->setObjectName(QString::fromUtf8("mytab"));
        mytab->setGeometry(QRect(0, 0, 311, 441));
        mytab->setMaximumSize(QSize(16777215, 531));
        main = new QWidget();
        main->setObjectName(QString::fromUtf8("main"));
        savebtn = new QPushButton(main);
        savebtn->setObjectName(QString::fromUtf8("savebtn"));
        savebtn->setGeometry(QRect(80, 250, 93, 28));
        view_all_stu = new QPushButton(main);
        view_all_stu->setObjectName(QString::fromUtf8("view_all_stu"));
        view_all_stu->setGeometry(QRect(60, 210, 151, 28));
        id_search = new QLineEdit(main);
        id_search->setObjectName(QString::fromUtf8("id_search"));
        id_search->setGeometry(QRect(110, 80, 151, 21));
        id_search->setClearButtonEnabled(true);
        label = new QLabel(main);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 80, 91, 20));
        label_2 = new QLabel(main);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1, 120, 111, 20));
        name_search = new QLineEdit(main);
        name_search->setObjectName(QString::fromUtf8("name_search"));
        name_search->setGeometry(QRect(110, 120, 151, 21));
        freshbtn = new QPushButton(main);
        freshbtn->setObjectName(QString::fromUtf8("freshbtn"));
        freshbtn->setGeometry(QRect(80, 290, 93, 28));
        mytab->addTab(main, QString());
        student = new QWidget();
        student->setObjectName(QString::fromUtf8("student"));
        view_stu_grd = new QPushButton(student);
        view_stu_grd->setObjectName(QString::fromUtf8("view_stu_grd"));
        view_stu_grd->setGeometry(QRect(30, 180, 121, 28));
        add_stu = new QPushButton(student);
        add_stu->setObjectName(QString::fromUtf8("add_stu"));
        add_stu->setGeometry(QRect(30, 230, 121, 28));
        adjustbtn = new QPushButton(student);
        adjustbtn->setObjectName(QString::fromUtf8("adjustbtn"));
        adjustbtn->setGeometry(QRect(30, 280, 121, 28));
        del_stu = new QPushButton(student);
        del_stu->setObjectName(QString::fromUtf8("del_stu"));
        del_stu->setGeometry(QRect(30, 330, 121, 28));
        id_mhss = new QLineEdit(student);
        id_mhss->setObjectName(QString::fromUtf8("id_mhss"));
        id_mhss->setGeometry(QRect(120, 40, 113, 21));
        label_4 = new QLabel(student);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(21, 40, 91, 20));
        label_5 = new QLabel(student);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 111, 20));
        name_mhss = new QLineEdit(student);
        name_mhss->setObjectName(QString::fromUtf8("name_mhss"));
        name_mhss->setGeometry(QRect(120, 100, 113, 21));
        mytab->addTab(student, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        view_grade = new QPushButton(tab);
        view_grade->setObjectName(QString::fromUtf8("view_grade"));
        view_grade->setGeometry(QRect(20, 100, 161, 28));
        view_all_crs = new QPushButton(tab);
        view_all_crs->setObjectName(QString::fromUtf8("view_all_crs"));
        view_all_crs->setGeometry(QRect(20, 50, 161, 28));
        mytab->addTab(tab, QString());
        System->setCentralWidget(centralwidget);
        menubar = new QMenuBar(System);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 330, 26));
        System->setMenuBar(menubar);
        statusbar = new QStatusBar(System);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        System->setStatusBar(statusbar);

        retranslateUi(System);

        mytab->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(System);
    } // setupUi

    void retranslateUi(QMainWindow *System)
    {
        System->setWindowTitle(QCoreApplication::translate("System", "System", nullptr));
        savebtn->setText(QCoreApplication::translate("System", "\344\277\235\345\255\230", nullptr));
        view_all_stu->setText(QCoreApplication::translate("System", "\346\237\245\347\234\213\346\211\200\346\234\211\345\255\246\347\224\237\344\277\241\346\201\257", nullptr));
        id_search->setText(QString());
        label->setText(QCoreApplication::translate("System", "id\345\244\264\351\203\250\346\220\234\347\264\242", nullptr));
        label_2->setText(QCoreApplication::translate("System", "\345\220\215\345\255\227\345\244\264\351\203\250\346\220\234\347\264\242", nullptr));
        freshbtn->setText(QCoreApplication::translate("System", "\345\210\267\346\226\260", nullptr));
        mytab->setTabText(mytab->indexOf(main), QCoreApplication::translate("System", "main", nullptr));
        view_stu_grd->setText(QCoreApplication::translate("System", "\346\237\245\347\234\213\345\255\246\347\224\237\346\210\220\347\273\251", nullptr));
        add_stu->setText(QCoreApplication::translate("System", "\346\267\273\345\212\240\345\255\246\347\224\237\344\277\241\346\201\257", nullptr));
        adjustbtn->setText(QCoreApplication::translate("System", "\344\277\256\346\224\271\345\255\246\347\224\237\344\277\241\346\201\257", nullptr));
        del_stu->setText(QCoreApplication::translate("System", "\345\210\240\351\231\244\345\255\246\347\224\237\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("System", "id\346\250\241\347\263\212\346\220\234\347\264\242", nullptr));
        label_5->setText(QCoreApplication::translate("System", "\345\220\215\345\255\227\346\250\241\347\263\212\346\220\234\347\264\242", nullptr));
        mytab->setTabText(mytab->indexOf(student), QCoreApplication::translate("System", "student", nullptr));
        view_grade->setText(QCoreApplication::translate("System", "\346\237\245\347\234\213\345\215\225\351\227\250\350\257\276\347\250\213\346\210\220\347\273\251", nullptr));
        view_all_crs->setText(QCoreApplication::translate("System", "\346\237\245\347\234\213\346\211\200\346\234\211\350\257\276\347\250\213\344\277\241\346\201\257", nullptr));
        mytab->setTabText(mytab->indexOf(tab), QCoreApplication::translate("System", "course", nullptr));
    } // retranslateUi

};

namespace Ui {
    class System: public Ui_System {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEM_H
