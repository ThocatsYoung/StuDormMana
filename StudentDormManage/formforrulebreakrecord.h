#ifndef FORMFORRULEBREAKRECORD_H
#define FORMFORRULEBREAKRECORD_H

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QAbstractTableModel>

#include <QListWidget>
#include <QLayout>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>

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
    void on_pushButton_add_outsider_record_clicked();

    void on_pushButton_finish_outsider_record_clicked();

    void on_pushButton_clicked();

    void on_pushButton_show_past_clicked();

private:
    Ui::FormForRuleBreakRecord *ui;
    QString file_path;
    QString past_file_path;
    RuleBreakRecordModel *model_records;
    QList<record_rulebreak> *data_records;
    QList<record_rulebreak> *data_pastrecords;
};

#endif // FORMFORRULEBREAKRECORD_H
