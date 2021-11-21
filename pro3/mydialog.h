#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include<QString>

namespace Ui {
class myDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    QString name;
    int grade;
    explicit myDialog(QWidget *parent = nullptr);
    ~myDialog();

private slots:
    void on_closebtn_clicked();

    void on_finishbtn_clicked();

private:
    Ui::myDialog *ui;

};

#endif // MYDIALOG_H
