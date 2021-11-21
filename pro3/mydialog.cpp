#include "mydialog.h"
#include "ui_mydialog.h"

myDialog::myDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);
}

myDialog::~myDialog()
{
    delete ui;
}

void myDialog::on_closebtn_clicked()
{
    close();
}

void myDialog::on_finishbtn_clicked()
{
    name = ui->nametext->text();
    grade = ui->gradetext->text().toInt();
}
