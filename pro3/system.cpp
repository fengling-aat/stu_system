#include "system.h"
#include "ui_system.h"

#define _CRT_SECURE_NO_WARNINGS

System::System(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::System)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("info_system"));
   //QCompleter *C = new QCompleter(id_list,this);
   //C->setCaseSensitivity(Qt::CaseInsensitive);
   //ui->normal_search->setCompleter(C);
    connect(ui->id_search, &QLineEdit::returnPressed, this, &System::search_id);
    connect(ui->name_search, &QLineEdit::returnPressed, this, &System::search_name);
    connect(ui->id_mhss, &QLineEdit::returnPressed, this, &System::mhss_id);
    connect(ui->name_mhss, &QLineEdit::returnPressed, this, &System::mhss_name);
   // connect(ui->gjss_line, &QLineEdit::returnPressed, this, &System::advanced_search);

}

System::~System()
{
    delete ui;
}



void System::add_students() {
    string id, name, department;
    int Class;
    bool ok;
    QString q_id = QInputDialog::getText(this, tr(""),
                                         tr("id:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if(!ok){
        QMessageBox::information(this,"","添加失败");
        return;
    }
    id = qstr2str(q_id);
    for (student i:stu_list) {
        if (i.get_id() == id) {
            QMessageBox::information(this,"","id已存在");
            return;
        }
    }
    QString q_name = QInputDialog::getText(this, tr(""),
                                         tr("名字:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    name = qstr2str(q_name);
    if(!ok){
        QMessageBox::information(this,"","添加失败");
        return;
    }

    QStringList majors;
    majors << "计算机"<<"数学"<<"人工智能";
    QString major = QInputDialog::getItem(this,"","专业为：",majors,0,false);
    department = qstr2str(major);
    Class = QInputDialog::getInt(this,"","班级:",1,1,5,1);
    student ns(id, name, department, Class);
    stu_list.push_back(ns);
    id_list.append(str2qstr(id));
    name_list.append(str2qstr(name));
    QMessageBox::information(this,"","添加成功");
}

void System::del_student() {
    string id;
    bool ok;
    QString q_id = QInputDialog::getText(this, tr(""),
                                         tr("id:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    id = qstr2str(q_id);
    if(!ok){
        QMessageBox::information(this,"","删除失败");
        return;
    }
    bool flag = 0;
    for (int i = 0; i < stu_list.size(); i++) {
        if (stu_list[i].get_id() == id) {
            stu_list.erase(stu_list.begin() + i);
            id_list.removeOne(str2qstr(id));
            name_list.removeOne(str2qstr(stu_list[i].name));
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        QMessageBox::information(this,"","不存在这个学号");
        return;
    }
    string filename = id + ".txt";
    remove(filename.c_str());
    QMessageBox::information(this,"","删除成功");
}

bool System::sys_read() {
    FILE* fp1 = fopen("course.txt", "r");
    if (fp1 == NULL) {
        qDebug() << "文件不存在" << endl;
        return 0;
    }
    int line_num = 0;
    char ch;
    while ((ch = fgetc(fp1)) != EOF) {
        if (ch == '\n')
            line_num++;
    }
    rewind(fp1);
    char course_name[20];
    int credit;
    for (int i = 0; i < line_num-1; i++) {
        fscanf(fp1, "%s %d\n", course_name, &credit);
        string courseName = course_name;
        //courses.insert({ course_name,credit });
        courses.push_back(lesson(courseName, credit));
    }
    fclose(fp1);
    //for (lesson i : courses)
        //i.show_grade_list();
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL){
        qDebug() << "文件不存在" << endl;
        return 0;
    }
    //char ch;
    char id_temp[20], name_temp[20], department_temp[20];
    int class_temp;
    line_num = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            line_num++;
    }
    rewind(fp);
    for (int i = 0; i < line_num; i++) {
        fscanf(fp, "%s %s %s %d\n", id_temp, name_temp, department_temp, &class_temp);
        string id = id_temp, name = name_temp, department = department_temp;
        student temp(id, name, department, class_temp);
        //temp.show_without_grade();
        temp.read(courses);
        stu_list.push_back(temp);
        departs.insert(department);
        classes.insert(class_temp);
    }
    fclose(fp);

    for(student stu:stu_list){
        id_list.append(str2qstr(stu.id));
        name_list.append((str2qstr(stu.name)));
    }

    QCompleter *id_C = new QCompleter(id_list,this);
    id_C->setCaseSensitivity(Qt::CaseInsensitive);
    ui->id_search->setCompleter(id_C);
    QCompleter *name_C = new QCompleter(name_list,this);
    name_C->setCaseSensitivity(Qt::CaseInsensitive);
    ui->name_search->setCompleter(name_C);
    return 1;
}

bool System::sys_save() {
    FILE* fp = fopen("student.txt", "w");
    if (fp == NULL)
        return 0;
    for (int i = 0; i < stu_list.size(); i++) {
        string ID= stu_list[i].get_id();
        string NAME = stu_list[i].get_name();
        string DEPARTMENT = stu_list[i].get_department();
        int CLASS = stu_list[i].get_class();
        fprintf(fp, "%s %s %s %d\n",ID.c_str(),NAME.c_str(),DEPARTMENT.c_str(),CLASS);
        stu_list[i].save();
    }
    fclose(fp);
    QMessageBox::information(this,"","保存成功");
    return 1;
}

void System::sys_show() {
    for (int i = 0; i < stu_list.size(); i++) {
        stu_list[i].display();
    }
}

void System::find_by_department() {
    string department;
    cout << "请输入院系：";
    cin >> department;
    bool flag = 0;
    for (int i = 0; i < stu_list.size(); i++) {
        if (is_name_match(department, stu_list[i].get_department())) {
            stu_list[i].display();
            cout << endl;
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "不存在这个院系" << endl;
}

void System::sys_find() {
    int chos;
    cout << "1.根据名字  2.根据学号  3.根据院系  4.高级搜索" << endl;
    cout << "请输入你的选择：";
    //cin >> chos;
    while (!(cin >> chos))
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cout << "输入有误，重新输入:";
    }
    switch (chos) {
    //case(1):find_by_name(); break;
    //case(2):find_by_id(); break;
    case(3):find_by_department(); break;
    //case(4):advanced_search(); break;
    default:cout << "输入不合法" << endl; break;
    }
}



void System::adjust() {
    string id;
    bool ok;
    QString q_id = QInputDialog::getText(this, tr("id"),tr("id:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
    if(!ok){
        QMessageBox::information(this,"","修改失败");
        return;
    }
    id = qstr2str(q_id);
    bool flag = 0;
    for (int stu_idx = 0;stu_idx < stu_list.size();stu_idx++) {
        if (id == stu_list[stu_idx].get_id()) {
            //stu_list[i].adjust_info(courses);
            flag = 1;
            QStringList choices;
            choices << "修改成绩"<<"添加成绩";
            QString chos = QInputDialog::getItem(this,"","选择为：",choices,0,false);
            if(chos == QString("修改成绩")){
                myDialog* dlg = new myDialog;
                dlg->exec();
                qDebug() << dlg->name <<" "<<dlg->grade<<endl;
                for(map<string, int>::iterator iter = stu_list[stu_idx].grades.begin(); iter != stu_list[stu_idx].grades.end(); iter++){
                    if(qstr2str(dlg->name) == iter->first){
                        if(iter->second != dlg->grade){
                            iter->second = dlg->grade;
                            for(int crs_idx =0;crs_idx < courses.size();crs_idx++){
                                if(courses[crs_idx].name == qstr2str(dlg->name)){
                                    courses[crs_idx].grades[id] = dlg->grade;
                                    break;
                                }
                            }
                            QMessageBox::information(this,"","修改成功");
                        }
                        else
                            QMessageBox::information(this,"","改了个寂寞");
                        return;
                    }
                }
                QMessageBox::information(this,"","没有该课程");
                return;
            }
            else if(chos == QString("添加成绩")){
                myDialog* dlg = new myDialog;
                dlg->exec();
                qDebug() << dlg->name <<" "<<dlg->grade<<endl;
                for(map<string, int>::iterator iter = stu_list[stu_idx].grades.begin(); iter != stu_list[stu_idx].grades.end(); iter++){
                    if(qstr2str(dlg->name) == iter->first){
                        QMessageBox::information(this,"","已有该课程，添加失败");
                        return;
                    }
                }
                for(int crs_idx =0;crs_idx < courses.size();crs_idx++){
                    if(courses[crs_idx].name == qstr2str(dlg->name)){
                        stu_list[stu_idx].grades.insert({courses[crs_idx].name,dlg->grade});
                        courses[crs_idx].add_info(id,dlg->grade);
                        QMessageBox::information(this,"","添加成功");
                        return;
                    }
                }
                QMessageBox::information(this,"","系统中没有该课程，添加失败");
                return;
            }
        }
    }
    if (flag == 0)
        QMessageBox::information(this,"","没有该学号，添加失败");
}
void System::find_department() {
    string department;
    cout << "输入院系：";
    cin >> department;
    bool flag = 0;
    for (int i = 0; i < stu_list.size(); i++) {
        if (department == stu_list[i].get_department()) {
            cout << stu_list[i].get_id() << " " << stu_list[i].get_name() << endl;
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "不存在这个院系" << endl;
}
void System::find_class() {
    int c;
    cout << "输入班级：";
    cin >> c;
    bool flag = 0;
    for (int i = 0; i < stu_list.size(); i++) {
        if (c == stu_list[i].get_class()) {
            cout << stu_list[i].get_id() << " " << stu_list[i].get_name() << endl;
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "不存在这个班级" << endl;
}
void System::find_course() {
    string course;
    cout << "输入课程名：";
    cin >> course;
    bool flag = 0;
    //for(map<string,int>::iterator it = courses.begin();it != courses.end();it++)
        //if (course == it->first) {
            //flag = 1;
            //break;
        //}
    for(lesson i:courses)
        if (course == i.get_name()) {
            flag = 1;
            break;
        }
    if (!flag) {
        cout << "不存在这个课程" << endl;
        return;
    }
    for (int i = 0; i < stu_list.size(); i++) {
        stu_list[i].find_course(course);
    }
}
void System::display() {
    cout << "所有的院系有：";
    for (set<string>::iterator it = departs.begin(); it != departs.end(); it++) {
        cout << *it << " ";
    }
    cout <<endl<< "所有的班级有：";
    for (set<int>::iterator it = classes.begin(); it != classes.end(); it++) {
        cout << *it << " ";
    }
    cout <<endl<< "所有的课程有：";
    for (lesson i:courses)
        cout << i.get_name() << " ";
    cout <<endl<< "1.院系 2.班级 3.课程" ;
    cout <<endl<< "请输入你的选择：";
    int chos;
    cin >> chos;
    switch (chos)
    {
    case 1:find_department(); break;
    case 2:find_class(); break;
    case 3:find_course(); break;
    default:
        break;
    }
}

void System::course_avg() {
    cout << endl << "所有的课程有：";
    for (lesson i:courses)
        cout << i.get_name() << " ";
    string course;
    cout <<endl<< "请输入课程名：";
    cin >> course;
    bool flag = 0;
    for (lesson i : courses)
        if (course == i.get_name()) {
            flag = 1;
            break;
        }
    if (!flag) {
        cout << "不存在这个课程" << endl;
        return;
    }
    float sum = 0;
    float student_num = 0;
    for (int i = 0; i < stu_list.size(); i++) {
        int grade = stu_list[i].course_grade(course);
        if (grade > 0) {
            sum += grade;
            student_num++;
        }
    }
    if (student_num == 0) {
        cout << "没有学生录入成绩" << endl;
        return;
    }
    float result = sum / student_num;
    cout << "平均分为：" << result << endl;
}

void System::show_course_grade() {
    for (lesson i : courses)
        i.show_grade_list();
}

void System::show_all_students() {
    mytable* stu_info_list = new mytable;
    stu_info_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStandardItemModel* model = new QStandardItemModel(stu_info_list);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal, "id");
    model->setHeaderData(1,Qt::Horizontal, "名字");
    model->setHeaderData(2,Qt::Horizontal, "院系");
    model->setHeaderData(3,Qt::Horizontal, "班级");
    model->setRowCount(stu_list.size());
    for(int i = 0;i < stu_list.size();i++){
        model->setHeaderData(i,Qt::Vertical,QString::number(i));
        model->setItem(i,0,new QStandardItem(str2qstr(stu_list[i].id)));
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,1,new QStandardItem(str2qstr(stu_list[i].name)));
        model->item(i,1)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,2,new QStandardItem(str2qstr(stu_list[i].department)));
        model->item(i,2)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,3,new QStandardItem(QString::number(stu_list[i].Class)));
        model->item(i,3)->setTextAlignment(Qt::AlignCenter);
    }

    stu_info_list->setModel(model);
    stu_info_list->show();
    for (student i : stu_list) {
        i.show_without_grade();
    }
}

void System::find_gpa() {
    string id;
    cout << "输入学号：";
    cin >> id;
    bool flag = 0;
    for (student i : stu_list) {
        if (id == i.get_id()) {
            cout <<"gpa:"<<i.get_gpa(courses);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "不存在这个学号" << endl;
}

void System::show_all_courses() {
    mytable* crs_list = new mytable;
    crs_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStandardItemModel* model = new QStandardItemModel(crs_list);
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal, "课程名称");
    model->setHeaderData(1,Qt::Horizontal, "学分");
    model->setRowCount(courses.size());
    for(int i = 0;i < courses.size();i++){
        model->setHeaderData(i,Qt::Vertical,QString::number(i));
        model->setItem(i,0,new QStandardItem(str2qstr(courses[i].name)));
        model->setItem(i,1,new QStandardItem(QString::number(courses[i].credit)));
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->item(i,1)->setTextAlignment(Qt::AlignCenter);
    }

    crs_list->setModel(model);
    for (lesson i : courses) {
        i.display();
    }
    crs_list->show();
}


void System::on_savebtn_clicked()
{
    sys_save();
}

void System::on_view_all_stu_clicked()
{
    qDebug()<<1;
    show_all_students();
}

void System::on_view_all_crs_clicked()
{
    show_all_courses();
}

void System::on_add_stu_clicked()
{
    add_students();
}

void System::on_del_stu_clicked()
{
    del_student();
}

void System::on_adjustbtn_clicked()
{
    adjust();
}

void System::on_view_grade_clicked()
{
    string crs_name;
    bool ok;
    QString q_name = QInputDialog::getText(this, tr(""),tr("课程名:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
    crs_name = qstr2str(q_name);
    if(!ok){
        QMessageBox::information(this,"","查找失败");
        return;
    }
    crs_name = qstr2str(q_name);
    for(lesson l:courses){
        if(l.name == crs_name){
            mytable* grd_list = new mytable;
            grd_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
            QStandardItemModel* model = new QStandardItemModel(grd_list);
            model->setColumnCount(2);
            model->setHeaderData(0,Qt::Horizontal, "学生id");
            model->setHeaderData(1,Qt::Horizontal, "成绩");
            model->setRowCount(l.grades.size()+1);
            std::map<string, int>::iterator it;
            int i;
            double sum = 0;
            for (it = l.grades.begin(),i = 0; it != l.grades.end(); it++,i++){
                model->setHeaderData(i,Qt::Vertical,QString::number(i));
                model->setItem(i,0,new QStandardItem(str2qstr(it->first)));
                model->setItem(i,1,new QStandardItem(QString::number(it->second)));
                model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                sum += it->second;
            }
            if(i > 0){
                double avg = sum/i;
                QString q_avg = QString("%1").arg(avg);
                model->setHeaderData(i,Qt::Vertical,QString::number(i));
                model->setItem(i,0,new QStandardItem(QString("平均分")));
                model->setItem(i,1,new QStandardItem(q_avg));
                model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                grd_list->setModel(model);
                grd_list->show();
            }
            else
                QMessageBox::information(this,"","没有成绩录入");
            return;
        }
    }
    QMessageBox::information(this,"","没有该课程");
}

void System::find_by_id(string id) {
    for(student stu:stu_list){
        if(stu.id == id){
            mytable* grd_list = new mytable;
            grd_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
            QStandardItemModel* model = new QStandardItemModel(grd_list);
            model->setColumnCount(2);
            model->setHeaderData(0,Qt::Horizontal, "type");
            model->setHeaderData(1,Qt::Horizontal, "data");
            model->setRowCount(stu.grades.size()+4);
            std::map<string, int>::iterator it;


            model->setHeaderData(0,Qt::Vertical,QString::number(0));
            model->setItem(0,0,new QStandardItem(QString("id")));
            model->setItem(0,1,new QStandardItem(str2qstr(id)));

            model->setHeaderData(1,Qt::Vertical,QString::number(1));
            model->setItem(1,0,new QStandardItem(QString("名字")));
            model->setItem(1,1,new QStandardItem(str2qstr(stu.name)));

            model->setHeaderData(2,Qt::Vertical,QString::number(2));
            model->setItem(2,0,new QStandardItem(QString("院系")));
            model->setItem(2,1,new QStandardItem(str2qstr(stu.department)));

            model->setHeaderData(3,Qt::Vertical,QString::number(3));
            model->setItem(3,0,new QStandardItem(QString("班级")));
            model->setItem(3,1,new QStandardItem(QString::number(stu.Class)));

            for(int j = 0;j < 4;j++){
                model->item(j,0)->setTextAlignment(Qt::AlignCenter);
                model->item(j,1)->setTextAlignment(Qt::AlignCenter);
            }

            int i = 4;

            for (it = stu.grades.begin(); it != stu.grades.end(); it++,i++){
                qDebug() << i << endl;
                model->setHeaderData(i,Qt::Vertical,QString::number(i));
                model->setItem(i,0,new QStandardItem(str2qstr(it->first)));
                model->setItem(i,1,new QStandardItem(QString::number(it->second)));
                model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                model->item(i,1)->setTextAlignment(Qt::AlignCenter);
            }

            if(i>4){
                qDebug() << str2qstr(id) << "has grade"<< i <<endl;
                float gpa = stu.get_gpa(courses);
                QString q_gpa = QString("%1").arg(gpa);
                model->setHeaderData(i,Qt::Vertical,QString::number(i-1));
                model->setItem(i,0,new QStandardItem(QString("gpa")));
                model->setItem(i,1,new QStandardItem(q_gpa));
                model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                model->item(i,1)->setTextAlignment(Qt::AlignCenter);
            }
            grd_list->setModel(model);
            grd_list->show();
            return;
        }
    }
    QMessageBox::information(this,"","没有该id");
}

void System::find_by_name(string name){
    for(student stu:stu_list){
        if(stu.name == name){
            mytable* grd_list = new mytable;
            grd_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
            QStandardItemModel* model = new QStandardItemModel(grd_list);
            model->setColumnCount(2);
            model->setHeaderData(0,Qt::Horizontal, "type");
            model->setHeaderData(1,Qt::Horizontal, "data");
            model->setRowCount(stu.grades.size()+4);
            std::map<string, int>::iterator it;


            model->setHeaderData(0,Qt::Vertical,QString::number(0));
            model->setItem(0,0,new QStandardItem(QString("id")));
            model->setItem(0,1,new QStandardItem(str2qstr(stu.id)));

            model->setHeaderData(1,Qt::Vertical,QString::number(1));
            model->setItem(1,0,new QStandardItem(QString("名字")));
            model->setItem(1,1,new QStandardItem(str2qstr(stu.name)));

            model->setHeaderData(2,Qt::Vertical,QString::number(2));
            model->setItem(2,0,new QStandardItem(QString("院系")));
            model->setItem(2,1,new QStandardItem(str2qstr(stu.department)));

            model->setHeaderData(3,Qt::Vertical,QString::number(3));
            model->setItem(3,0,new QStandardItem(QString("班级")));
            model->setItem(3,1,new QStandardItem(QString::number(stu.Class)));

            for(int j = 0;j < 4;j++){
                model->item(j,0)->setTextAlignment(Qt::AlignCenter);
                model->item(j,1)->setTextAlignment(Qt::AlignCenter);
            }

            int i = 4;

            for (it = stu.grades.begin(); it != stu.grades.end(); it++,i++){
                qDebug() << i << endl;
                model->setHeaderData(i,Qt::Vertical,QString::number(i));
                model->setItem(i,0,new QStandardItem(str2qstr(it->first)));
                model->setItem(i,1,new QStandardItem(QString::number(it->second)));
                model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                model->item(i,1)->setTextAlignment(Qt::AlignCenter);
            }

            if(i>4){
                qDebug() << str2qstr(name) << "has grade"<< i <<endl;
                float gpa = stu.get_gpa(courses);
                QString q_gpa = QString("%1").arg(gpa);
                model->setHeaderData(i,Qt::Vertical,QString::number(i-1));
                model->setItem(i,0,new QStandardItem(QString("gpa")));
                model->setItem(i,1,new QStandardItem(q_gpa));
                model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                model->item(i,1)->setTextAlignment(Qt::AlignCenter);
            }
            grd_list->setModel(model);
            grd_list->show();
            return;
        }
    }
    QMessageBox::information(this,"","没有该名字");
}

void System::on_view_stu_grd_clicked()
{
    string id;
    bool ok;
    QString q_id = QInputDialog::getText(this, tr(""),tr("id:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
    id = qstr2str(q_id);
    if(!ok){
        QMessageBox::information(this,"","查找失败");
        return;
    }
    find_by_id(id);
}

void System::search_id(){
    QString q_id = ui->id_search->text();
    qDebug()<<q_id;
    string id = qstr2str(q_id);
    find_by_id(id);
}

void System::search_name(){
    QString q_name = ui->name_search->text();
    qDebug()<<q_name;
    string name =qstr2str(q_name);
    find_by_name(name);
}

void System::mhss_id(){
    QString q_info = ui->id_mhss->text();
    qDebug()<<q_info;
    string id_info = qstr2str(q_info);

    mytable* _list = new mytable;
    _list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStandardItemModel* model = new QStandardItemModel(_list);
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal, "type");
    model->setHeaderData(1,Qt::Horizontal, "data");
    //model->setRowCount(100);

    int line = 0;

    for(student stu:stu_list){
        if(is_id_match(id_info,stu.id)){
            qDebug() << str2qstr(stu.id)<<endl;
            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("id")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.id)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("名字")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.name)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("院系")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.department)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("班级")));
            model->setItem(line,1,new QStandardItem(QString::number(stu.Class)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            std::map<string, int>::iterator it;
            for (it = stu.grades.begin(); it != stu.grades.end(); it++,line++){
                qDebug() << line << endl;
                model->setHeaderData(line,Qt::Vertical,QString::number(line));
                model->setItem(line,0,new QStandardItem(str2qstr(it->first)));
                model->setItem(line,1,new QStandardItem(QString::number(it->second)));
                model->item(line,0)->setTextAlignment(Qt::AlignCenter);
                model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            }

            if(stu.grades.size() > 0){
                float gpa = stu.get_gpa(courses);
                QString q_gpa = QString("%1").arg(gpa);
                model->setHeaderData(line,Qt::Vertical,QString::number(line));
                model->setItem(line,0,new QStandardItem(QString("gpa")));
                model->setItem(line,1,new QStandardItem(q_gpa));
                model->item(line,0)->setTextAlignment(Qt::AlignCenter);
                model->item(line,1)->setTextAlignment(Qt::AlignCenter);
                line++;
            }

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("")));
            model->setItem(line,1,new QStandardItem(QString("")));
            line++;
        }
    }
    if(line == 0){
        QMessageBox::information(this,"","搜索失败");
    }
    else{
        _list->setModel(model);
        _list->show();
    }

}
void System::mhss_name(){
    QString q_info = ui->name_mhss->text();
    qDebug()<<q_info;
    string name_info = qstr2str(q_info);

    mytable* _list = new mytable;
    _list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStandardItemModel* model = new QStandardItemModel(_list);
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal, "type");
    model->setHeaderData(1,Qt::Horizontal, "data");
    //model->setRowCount(100);

    int line = 0;

    for(student stu:stu_list){
        if(is_name_match(name_info,stu.name)){
            qDebug() << str2qstr(stu.id)<<endl;
            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("id")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.id)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("名字")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.name)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("院系")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.department)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("班级")));
            model->setItem(line,1,new QStandardItem(QString::number(stu.Class)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            std::map<string, int>::iterator it;
            for (it = stu.grades.begin(); it != stu.grades.end(); it++,line++){
                qDebug() << line << endl;
                model->setHeaderData(line,Qt::Vertical,QString::number(line));
                model->setItem(line,0,new QStandardItem(str2qstr(it->first)));
                model->setItem(line,1,new QStandardItem(QString::number(it->second)));
                model->item(line,0)->setTextAlignment(Qt::AlignCenter);
                model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            }

            if(stu.grades.size() > 0){
                float gpa = stu.get_gpa(courses);
                QString q_gpa = QString("%1").arg(gpa);
                model->setHeaderData(line,Qt::Vertical,QString::number(line));
                model->setItem(line,0,new QStandardItem(QString("gpa")));
                model->setItem(line,1,new QStandardItem(q_gpa));
                model->item(line,0)->setTextAlignment(Qt::AlignCenter);
                model->item(line,1)->setTextAlignment(Qt::AlignCenter);
                line++;
            }

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("")));
            model->setItem(line,1,new QStandardItem(QString("")));
            line++;
        }
    }
    if(line == 0){
        QMessageBox::information(this,"","搜索失败");
    }
    else{
        _list->setModel(model);
        _list->show();
    }
}

/*void System::advanced_search() {
    QString q_info = ui->gjss_line->text();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    string info = qstr2str(q_info);

    qDebug() << str2qstr(info);

    mytable* _list = new mytable;
    _list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStandardItemModel* model = new QStandardItemModel(_list);
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal, "type");
    model->setHeaderData(1,Qt::Horizontal, "data");
   //model->setRowCount(100);

    int line = 0;

    for(student stu:stu_list){
        if(stu.advanced_search(info)){
            qDebug() << str2qstr(stu.id)<<endl;
            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("id")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.id)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("名字")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.name)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("院系")));
            model->setItem(line,1,new QStandardItem(str2qstr(stu.department)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("班级")));
            model->setItem(line,1,new QStandardItem(QString::number(stu.Class)));
            model->item(line,0)->setTextAlignment(Qt::AlignCenter);
            model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            line++;

            std::map<string, int>::iterator it;
            for (it = stu.grades.begin(); it != stu.grades.end(); it++,line++){
                qDebug() << line << endl;
                model->setHeaderData(line,Qt::Vertical,QString::number(line));
                model->setItem(line,0,new QStandardItem(str2qstr(it->first)));
                model->setItem(line,1,new QStandardItem(QString::number(it->second)));
                model->item(line,0)->setTextAlignment(Qt::AlignCenter);
                model->item(line,1)->setTextAlignment(Qt::AlignCenter);
            }
            model->setHeaderData(line,Qt::Vertical,QString::number(line));
            model->setItem(line,0,new QStandardItem(QString("")));
            model->setItem(line,1,new QStandardItem(QString("")));
            line++;
        }
    }
    if(line == 0){
        QMessageBox::information(this,"","搜索失败");
    }
    else{
        _list->setModel(model);
        _list->show();
    }
}*/



void System::on_freshbtn_clicked()
{
    stu_list.clear();
    courses.clear();
    id_list.clear();
    name_list.clear();
    sys_read();
}
