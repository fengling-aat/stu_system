#ifndef MYTABLE_H
#define MYTABLE_H

#include <QWidget>
#include<QTableView>

namespace Ui {
class mytable;
}

class mytable : public QTableView
{
    Q_OBJECT

public:
    explicit mytable(QWidget *parent = nullptr);
    ~mytable();

private:
    Ui::mytable *ui;
};

#endif // MYTABLE_H
