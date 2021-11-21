#ifndef SEARCH_H
#define SEARCH_H

#include<regex>
#include<QDebug>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<iostream>
#include <QWidget>
#include<QTableWidget>
#include<QStringList>
#include<QObject>
#include<QMenu>
#include<QLayout>
#include<QTableWidget>
#include<QObject>
#include<QSize>
#include<QString>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QContextMenuEvent>
#include<QVector>
#include<QComboBox>
#include<QLineEdit>
#include<QInputDialog>
#include<QStandardItemModel>
#include<QTableView>
#include<QTableWidget>
#include <QCompleter>
#include<QTextCodec>
using namespace std;

bool is_name_match(string a,const string& b);
bool is_id_match(string a, const string& b);
vector<string> split(const string& src, string separate_character);
QString str2qstr(const string str);
string qstr2str(const QString qstr);

#endif // SEARCH_H

