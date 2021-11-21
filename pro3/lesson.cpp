#include"lesson.h"

lesson::lesson() {
    name = "none";
    //department = "none";
    credit = 0;
}

lesson::lesson(string Name, int Credit) {
    name = Name;
    credit = Credit;
}

string lesson::get_name() {
    return name;
}

//string lesson::get_department() {
    //return department;
//}

int lesson::get_credit() {
    return credit;
}

void lesson::add_info(string stu_id, int grade) {
    grades.insert({stu_id,grade});
}

void lesson::show_grade_list() {
    cout << name << ":" << endl;
    //cout << "student_id grade" << endl;
    std::map<string, int>::iterator it;
    for (it = grades.begin(); it != grades.end(); it++)
        cout << it->first << " " << it->second << endl;
}

void lesson::adjust_grade(string id, int grade) {
    grades[id] = grade;
}

void lesson::display() {
    QString q_name = str2qstr(name);
    qDebug() << q_name << " " << credit << endl;
}
