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

//model
class outschoollistmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit outschoollistmodel(QObject *parent = 0);
    ~outschoollistmodel();

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
    QString file_path;
    QString past_file_path;
    outschoollistmodel *model_records;    //model
    QList<outschool> data_records;  //当前记录
    QList<outschool> data_pastrecords;  //历史记录
    QMap<QString, student*> *outmap;
};

#endif // FORMFOROUTSCHOOL_H
