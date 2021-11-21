#include "mytable.h"
#include "ui_mytable.h"
#include<QStandardItemModel>

mytable::mytable(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::mytable)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(this);
       /*设置列字段名*/
       model->setColumnCount(3);
       model->setHeaderData(0,Qt::Horizontal, "姓名");
       model->setHeaderData(1,Qt::Horizontal, "年龄");
       model->setHeaderData(2,Qt::Horizontal, "性别");
       /*设置行字段名*/
       model->setRowCount(3);
       model->setHeaderData(0,Qt::Vertical, "记录一");
       model->setHeaderData(1,Qt::Vertical, "记录二");
       model->setHeaderData(2,Qt::Vertical, "记录三");
       /*设置一条数据*/
       model->setItem(0, 0, new QStandardItem("张三"));
       model->setItem(0, 1, new QStandardItem("3"));
       model->setItem(0, 2, new QStandardItem("男"));
       this->setModel(model);
}

mytable::~mytable()
{
    delete ui;
}
