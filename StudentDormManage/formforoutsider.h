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

class wailairenlistmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit wailairenlistmodel(QObject *parent = 0);
    ~wailairenlistmodel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void setList_records(QList<outsider> *list_records);
    void add_new_record(outsider new_record);
private:
    QStringList headers;
    QList<outsider> *m_list_records;

};



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
    QString file_path;
    QString past_file_path;
    wailairenlistmodel *model_records;    //model
    QList<outsider> data_records;  //当前记录
    QList<outsider> data_pastrecords;  //历史记录

};

#endif // FORMFOROUTSIDER_H
