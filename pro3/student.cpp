#define _CRT_SECURE_NO_WARNINGS
#include"student.h"
student::student() {
    id = "none";
    name = "none";
    department = "none";
    Class = 0;
}

student::student(string Id, string Name, string Department, int C) {
    id = Id;
    name = Name;
    department = Department;
    Class = C;
    search_str = id+" "+name+" "+department+" "+to_string(Class);
}

void student::adjust_name() {
    string newname;
    cout << "请输入新名字：";
    cin >> name;
    name = newname;
}
void student::adjust_class() {
    int c;
    cout << "请输入新班级：";
    cin >> c;
    Class = c;
}
void student::adjust_department() {
    string newd;
    cout << "请输入新院系：";
    cin >> newd;
    department = newd;
}
void student::adjust_score(vector<lesson>&courses) {
    cout << "输入课程名称：";
    string course;
    cin >> course;
    int flag = 0;
    int score;
    for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
        if (course == iter->first) {
            cout << "请输入成绩：";
            cin >> score;
            iter->second = score;
            flag = 1;
            int j;
            for (j = 0; j < courses.size(); j++)
                if (courses[j].get_name() == course) {
                    courses[j].adjust_grade(id, score);
                    break;
                }
            break;
        }
    }
    if (flag == 0)
        cout << "课程不存在" << endl;
}
string student::get_id() {
    return id;
}
string student::get_name() {
    return name;
}
string student::get_department() {
    return department;
}
int student::get_class() {
    return Class;
}
void student::add_info(vector<lesson>&courses) {
    int num;
    cout << "请输入添加的课程数:";
    cin >> num;
    if (num == 0)
        return;
    cout << "输入格式：课程名 成绩 （如果暂时没有成绩，可以填-1）" << endl;
    string course;
    int grade;
    for (int i = 0; i < num; i++) {
        cin >> course >> grade;
        bool flag1 = 1,flag2 = 0;
        for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
            if (course == iter->first) {
                cout << "该课程已存在" << endl;
                flag1 = 0;
                break;
            }
        }
        int j;
        for(j = 0;j < courses.size();j++)
            if (courses[j].get_name() == course) {
                flag2 = 1;
                break;
            }
        if (flag2 == 0)
            cout << "课程不在系统中" << endl;
        if (flag1 && flag2) {
            grades.insert({ course, grade });
            courses[j].add_info(id, grade);
        }
    }
}
void student::read(vector<lesson>& courses) {
    string fname = id + ".txt";
    const char* filename = fname.c_str();
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        return;
    char ch;
    int line_num = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            line_num++;
    }
    rewind(fp);
    char course_name[20];
    int grade;
    for (int i = 0; i < line_num; i++) {
        fscanf(fp, "%s %d\n", course_name,&grade);
        string course = course_name;
        grades.insert({ course, grade });
        int j;
        //bool is_course_existed = 0;
        for (j = 0; j < courses.size(); j++)
            //cout << courses[j].get_name() << " " << course << endl;
            if (courses[j].get_name() == course) {
                courses[j].add_info(id, grade);
                //is_course_existed = 1;
                break;
            }
        //if (is_course_existed == 0) {

        //}
    }
    fclose(fp);
}
void student::save() {
    string fname = id + ".txt";
    const char* filename = fname.c_str();
    FILE* fp = fopen(filename, "w");
    if (fp == NULL)
        return;
    for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
        fprintf(fp, "%s %d\n", iter->first.c_str(), iter->second);
    }
    fclose(fp);
}
void student::display(){
    cout << id << " " << name << " " << department << " " << Class <<"班" <<endl;
    for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }
}

void student::adjust_info(vector<lesson>& courses) {
    display();
    cout << "1.名字 2.院系 3.班级 4.修改课程成绩 5.添加课程成绩" << endl;
    int chos;
    cout << "请输入你的选择：";
    cin >> chos;
    switch (chos) {
    case 1:adjust_name(); break;
    case 2:adjust_department(); break;
    case 3:adjust_class(); break;
    case 4:adjust_score(courses); break;
    case 5:add_info(courses);break;
    default:break;
    }
    display();
}

void student::find_course(string course) {
    for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
        if (course == iter->first) {
            cout << id << " " << name << " : " << iter->second << endl;
            break;
        }
    }
}

int student::course_grade(string course) {
    for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
        if (course == iter->first) {
            return iter->second;
        }
    }
    return -1;
}

bool student::is_match(Cdt c) {
    qDebug()<<str2qstr(c.type)<<str2qstr(c.data)<<endl;
    if (is_name_match("课", c.type)) {
        for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
            if (is_name_match(c.data, iter->first)) {
                return true;
            }
        }
        return false;
    }
    else if (is_name_match("号", c.type) || is_id_match("id",c.type)) {
        qDebug()<<"here"<<endl;
        return is_id_match(c.data, id);
    }

    else if (is_name_match("院", c.type)) {
        qDebug()<<"here"<<endl;
        return is_name_match(c.data, department);
    }
    else if (is_name_match("名", c.type)) {
        qDebug()<<"here"<<endl;
        return is_name_match(c.data, name);
    }
    return false;
}

Cdt part(string s) {
    Cdt c;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == ' ' || s[i] == '\'' || s[i] == '\"' || s[i] == '(' || s[i] == ')') {
            s.erase(s.begin() + i);
            i--;
        }
    //cout << s << endl;
    string::size_type idx1 = s.find("!=");
    string::size_type idx2 = s.find("=");
    if (idx1 != string::npos) {
        c.is_eqaul = 0;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == '!' && s[i + 1] == '=' && i < s.size() - 2) {
                c.type = s.substr(0, i);
                c.data = s.substr(i + 2, s.size() - 1);
            }
    }
    else if (idx2 != string::npos) {
        c.is_eqaul = 1;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == '=' && i < s.size() - 1) {
                c.type = s.substr(0, i);
                c.data = s.substr(i + 1, s.size() - 1);
            }
    }
    else {
        c.data = c.type = "";
    }
    return c;
}

bool student::judge_cdt(Cdt c) {
    if (c.is_eqaul)
        return is_match(c);
    else
        return !is_match(c);
}

bool student::advanced_search(string info) {
    qDebug() << str2qstr(info);
    vector<Cdt>s;
    //int last = 0;
    Cdt cdt;
    vector<string>or_set = split(info, "||");

    for (int i = 0; i < or_set.size(); i++) {
        vector<string>and_set = split(or_set[i], "&&");
        bool flag = 1;
        for (int j = 0; j < and_set.size(); j++) {
            Cdt c = part(and_set[j]);
            if (!judge_cdt(c))
                flag = 0;
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

void student::show_without_grade() {
    QString q_id = str2qstr(id);
    QString q_name = str2qstr(name);
    QString q_department = str2qstr(department);
    qDebug() << q_id << " " << q_name << " " << q_department << " " << Class <<"班"<< endl;
}

int get_credit(string course_name, vector<lesson>& courses) {
    for (lesson i : courses)
        if (i.get_name() == course_name)
            return i.get_credit();
    return -1;
}

float student::get_gpa(vector<lesson>& courses) {
    double sum = 0;
    int credit_sum = 0;
    for (map<string, int>::iterator iter = grades.begin(); iter != grades.end(); iter++) {
        int credit = get_credit(iter->first, courses);
        if (credit) {
            credit_sum += credit;
            sum += ((double)iter->second) / 100 * (double)credit;
        }
    }
    return 5*(sum / (double)credit_sum);
}

bool student::find(QString qs){
    string s = qstr2str(qs);
    if(id.find(s) != string::npos){
        return true;
    }
    else if(name.find(s) != string::npos){
        return true;
    }
    else if(department.find(s) != string::npos){
        return true;
    }
    else if(qs.toInt() == Class){
        return true;
    }
    else
        return false;
}
