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

//model
class wanguilistmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit wanguilistmodel(QObject *parent = 0);
    ~wanguilistmodel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void setList_records(QList<outschool> *list_records);
    void add_new_record(outschool new_record);
private:
    QStringList headers;
    QList<outschool> *m_list_records;

};


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
    QString file_path;
    QString past_file_path;
    wanguilistmodel *model_records;    //model
    QList<outschool> data_records;  //当前记录
    QList<outschool> data_pastrecords;  //历史记录
    QMap<QString, student*> *outmap;
};

#endif // FORMFORWANGUI_H
