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


    void setList_records(QList<record_rulebreak> *list_records);
    void add_new_record(record_rulebreak new_record);

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
    explicit FormForRuleBreakRecord(QString path, QString past_path, QWidget *parent = 0);
    ~FormForRuleBreakRecord();

private slots:
    void on_pushButton_add_outsider_record_clicked();   //添加记录

    void on_pushButton_finish_outsider_record_clicked();    //删除记录

    void on_pushButton_clicked();   //将当前记录移入历史记录

    void on_pushButton_show_past_clicked(); //展示历史记录

private:
    Ui::FormForRuleBreakRecord *ui;
    QString file_path;
    QString past_file_path;
    RuleBreakRecordModel *model_records;    //model
    QList<record_rulebreak> *data_records;  //当前记录
    QList<record_rulebreak> *data_pastrecords;  //历史记录
};

#endif // FORMFORRULEBREAKRECORD_H
