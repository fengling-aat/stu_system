#ifndef SYSTEM_H
#define SYSTEM_H

#include <QMainWindow>
#include"student.h"
#include "mytable.h"
#include "mydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class System; }
QT_END_NAMESPACE

class System : public QMainWindow
{
    Q_OBJECT

public:
    System(QWidget *parent = nullptr);
    void add_students();
    void del_student();
    bool sys_read();
    bool sys_save();
    void sys_find();
    void adjust();
    void display();
    void sys_show();
    void find_department();
    void find_class();
    void find_course();
    void course_avg();
    void find_by_id(string);
    void find_by_name(string);
    void find_by_department();
    void advanced_search();
    void show_course_grade();
    void show_all_students();
    void show_all_courses();
    void find_gpa();
    void search_id();
    void search_name();
    void mhss_id();
    void mhss_name();
    ~System();

private slots:
    void on_savebtn_clicked();

    void on_view_all_stu_clicked();

    void on_view_all_crs_clicked();

    void on_add_stu_clicked();

    void on_del_stu_clicked();

    void on_adjustbtn_clicked();

    void on_view_grade_clicked();

    void on_view_stu_grd_clicked();

    //void on_searchline_cursorPositionChanged(int arg1, int arg2);

    //void on_searchline_textChanged(const QString &arg1);

    void on_freshbtn_clicked();

private:
    Ui::System *ui;
    QLineEdit *LineEdit;
    vector<student>stu_list;
    //map<string, int>courses;
    vector<lesson>courses;
    set<string>departs;
    set<int>classes;
    QWidget *widget;
    QStringList id_list;
    QStringList name_list;
};
#endif // SYSTEM_H
