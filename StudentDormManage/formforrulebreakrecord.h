#ifndef FORMFORRULEBREAKRECORD_H
#define FORMFORRULEBREAKRECORD_H

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
#include "record_rulebreak.h"
#include "dialog_rulebreak_add.h"


//宿舍违纪登记模块

//model部分
class RuleBreakRecordModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RuleBreakRecordModel(QObject *parent = 0);
    ~RuleBreakRecordModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void setList_records(QList<record_rulebreak> *list_records);    //设置源数据

private:
    QStringList headers;
    QList<record_rulebreak> *m_list_records;


};



//ui部分
namespace Ui {
class FormForRuleBreakRecord;
}

class FormForRuleBreakRecord : public QWidget
{
    Q_OBJECT

public:
    explicit FormForRuleBreakRecord(QString path, QString past_path,
                                    QSet<quint16> *p, QWidget *parent = 0);
    ~FormForRuleBreakRecord();

    void save_record_to_file(); //将记录保存至文件

private slots:

    void add_new_record(record_rulebreak new_record);

    //这两个按钮名字忘记改了...outsider -> rule breaker
    void on_pushButton_add_outsider_record_clicked();   //添加宿舍违纪记录
    void on_pushButton_finish_outsider_record_clicked();    //删除宿舍违纪记录

    void on_pushButton_clicked();   //将当前记录移入历史记录 按钮忘记改成对应名字了 （注意）
    void on_pushButton_show_past_clicked(); //展示历史记录

private:
    Ui::FormForRuleBreakRecord *ui;

    QString file_path;  //记录文件路径
    QString past_file_path; //历史记录文件路径

    QSet<quint16> *point_to_set_of_dorm_number;   //宿舍号集合
    RuleBreakRecordModel *model_records;    //model
    QList<record_rulebreak> data_records;  //宿舍违纪当前记录
    QList<record_rulebreak> data_pastrecords;  //宿舍违纪历史记录
};

#endif // FORMFORRULEBREAKRECORD_H
