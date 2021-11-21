#ifndef STUDENT_H
#define STUDENT_H


#include"lesson.h"

struct Cdt {
    string type;
    string data;
    bool is_eqaul;// =:1  or  !=:0
};

class student {
    //string id;
    //string name;
    //string department;
    //int Class;
    //map<string,int>grades;
public:
    string id;
    string name;
    string department;
    int Class;
    string search_str;//帮助搜索
    map<string,int>grades;
    student();
    student(string Id, string Name, string Department, int C);
    void adjust_name();
    void adjust_department();
    void adjust_class();
    void adjust_score(vector<lesson>&);
    void adjust_info(vector<lesson>&);
    string get_id();
    string get_name();
    string get_department();
    int get_class();
    void add_info(vector<lesson>& courses);
    void display();
    float get_gpa(vector<lesson>& courses);
    void read(vector<lesson>& courses);
    void save();
    void find_course(string course);
    int course_grade(string course);
    bool advanced_search(string info);
    bool is_match(Cdt c);
    bool judge_cdt(Cdt c);
    void show_without_grade();
    bool find(QString qs);
//private:
    //string id;
    //string name;
    //string department;
    //int Class;
    //map<string,int>grades;
};

#endif // STUDENT_H
