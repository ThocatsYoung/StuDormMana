#ifndef FORMFORWANGUI_H
#define FORMFORWANGUI_H

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

#include "read_from_file.h"
#include"people.h"
#include"outschool.h"


//model晚归登记模板
class wanguilistmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit wanguilistmodel(QObject *parent = 0);
    ~wanguilistmodel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;//设置表头

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;     //计算行数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;  //计算列数

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;//设置表格数据


    void setList_records(QList<outschool> *list_records);//设置晚归记录链表
    void add_new_record(outschool new_record);//添加晚归记录
private:
    QStringList headers;             //表头数据
    QList<outschool> *m_list_records;//晚归记录链表

};



//ui晚归记录界面
namespace Ui {
class Formforwangui;
}

class Formforwangui : public QWidget
{
    Q_OBJECT

public:
    explicit Formforwangui(QString path, QString past_path,  QMap<QString, student*> *map, QWidget *parent = 0);
    ~Formforwangui();

private slots:
    void on_pushButton_clicked();   //添加

    void on_pushButton_3_clicked(); //删除

    void on_pushButton_2_clicked(); //写入历史记录

    void on_pushButton_4_clicked(); //显示历史记录

private:
    Ui::Formforwangui *ui;
    QString file_path;              //晚归登记文件路径
    QString past_file_path;         //晚归历史记录文件路径
    wanguilistmodel *model_records;    //model晚归登记
    QList<outschool> data_records;  //当前记录
    QList<outschool> data_pastrecords;  //历史记录
    QMap<QString, student*> *outmap;  //晚归登记map
};

#endif // FORMFORWANGUI_H
