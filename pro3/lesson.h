#ifndef LESSON_H
#define LESSON_H


#include"search.h"

class lesson {
    //string name;
    //string department;
    //int credit;
    //map<string,int>grades; //(stu_id,grade)
public:
    string name;
    //string department;
    int credit;
    map<string,int>grades; //(stu_id,grade)
    lesson();
    lesson(string Name, int Credit);
    string get_name();
    //string get_department();
    int get_credit();
    void add_info(string stu_id, int grade);
    void show_grade_list();
    void adjust_grade(string id, int grade);
    void display();
//private:
   // string name;
    //string department;
    //int credit;
    //map<string,int>grades; //(stu_id,grade)
};


#endif // LESSON_H
