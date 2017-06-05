#ifndef FORMFOROUTSIDER_H
#define FORMFOROUTSIDER_H

#include "read_from_file.h"

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QAbstractTableModel>

#include <QListWidget>
#include <QLayout>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>

#include "wailairen.h"
#include "dialog_wailairen_add.h"



//model外来人员模板
class wailairenlistmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit wailairenlistmodel(QObject *parent = 0);
    ~wailairenlistmodel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;//设置表头

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;                               //计算行数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;                            //计算列数

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;                   //设置表格数据


    void setList_records(QList<outsider> *list_records);        //设置外来人员链表
    void add_new_record(outsider new_record);                   //添加外来人员记录
private:
    QStringList headers;             //表头数据
    QList<outsider> *m_list_records;//外来人员链表

};


//ui外来人员界面
namespace Ui {
class FormForOutsider;
}

class FormForOutsider : public QWidget
{
    Q_OBJECT

public:
    explicit FormForOutsider(QString path, QString past_path, QWidget *parent = 0);
    ~FormForOutsider();
private slots:
    void on_pushButton_add_outsider_record_clicked();   //添加外来人

    void on_pushButton_finish_outsider_record_clicked();    //删除记录

    void on_pushButton_clicked();   //将当前记录移入历史记录

    void on_pushButton_show_past_clicked(); //展示历史记录

private:
    Ui::FormForOutsider *ui;
    QString file_path;                //外来人员文件路径
    QString past_file_path;           //外来人员历史记录文件路径
    wailairenlistmodel *model_records;    //model外来人
    QList<outsider> data_records;  //当前记录
    QList<outsider> data_pastrecords;  //历史记录

};

#endif // FORMFOROUTSIDER_H
