#ifndef FORMFOROUTSCHOOL_H
#define FORMFOROUTSCHOOL_H

#include "read_from_file.h"

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QAbstractTableModel>
#include <QMap>

#include <QListWidget>
#include <QLayout>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>

#include"people.h"
#include"outschool.h"



     //model离校登记模板
class outschoollistmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit outschoollistmodel(QObject *parent = 0);
    ~outschoollistmodel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;//表头信息

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;     //计算行数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;  //计算列数

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;//设置显示的信息


    void setList_records(QList<outschool> *list_records);       //设置离校记录链表
    void add_new_record(outschool new_record);                  //添加记录
private:
    QStringList headers;                                     //表头
    QList<outschool> *m_list_records;                        //离校记录链表

};



//ui离校记录ui界面
namespace Ui {
class Formforoutschool;
}

class Formforoutschool : public QWidget
{
    Q_OBJECT

public:
    explicit Formforoutschool(QString path, QString past_path,  QMap<QString, student*> *map,QWidget *parent = 0);
    ~Formforoutschool();


private slots:

    void on_pushButton_clicked();//添加离校记录

    void on_pushButton_2_clicked();//删除显示项

    void on_pushButton_3_clicked();//写入历史记录

    void on_pushButton_4_clicked();//显示历史记录

private:
    Ui::Formforoutschool *ui;
    QString file_path;            //离校记录文件路径
    QString past_file_path;       //离校历史记录文件路径
    outschoollistmodel *model_records;    //model
    QList<outschool> data_records;  //当前记录
    QList<outschool> data_pastrecords;  //历史记录
    QMap<QString, student*> *outmap;    //离校记录map
};

#endif // FORMFOROUTSCHOOL_H
