#ifndef DORM_REPAIR_SHOW_H
#define DORM_REPAIR_SHOW_H

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QAbstractTableModel>

#include <QListWidget>
#include <QLayout>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>

#include "read_from_file.h"
#include "dorm_repair.h"
#include "dialog_addrepair.h"


//model
class dorm_repair_model: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit dorm_repair_model(QObject *parent = 0);
    ~dorm_repair_model();

    //header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //basic functionality
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setList_dorm_repair(QList<dorm_repair> *list_dorm_repair);
    void add_new_dorm_repair(dorm_repair Dorm_repair);

private:
    QStringList headers;
    QList<dorm_repair> *m_list_dorm_repair;
};



//ui
namespace Ui {
class dorm_repair_show;
}

class dorm_repair_show : public QWidget
{
    Q_OBJECT

public:
    explicit dorm_repair_show(QString path, QString finish_path, QWidget *parent = 0);
    ~dorm_repair_show();

private slots:
    void on_pushButton_add_repair_clicked();

    void on_pushButton_finish_clicked();

    void on_pushButton_repair_record_clicked();

private:
    Ui::dorm_repair_show *ui;
    QString dorm_repair_file_path;          //宿舍报修记录
    QString finish_file_path;               //宿舍维修完成记录
    dorm_repair_model *model_dorm_repair;   //model
    QList<dorm_repair> *data_dorm_need_to_repair;   //报修记录
    QList<repair_record> *data_finish;      //维修记录

};

#endif // DORM_REPAIR_SHOW_H
