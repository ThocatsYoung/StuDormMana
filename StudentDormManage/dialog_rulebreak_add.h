#ifndef DIALOG_RULEBREAK_ADD_H
#define DIALOG_RULEBREAK_ADD_H

#include "read_from_file.h"

#include <QDialog>
#include <QSet>

#include "formforrulebreakrecord.h"



namespace Ui {
class Dialog_rulebreak_add;
}

class Dialog_rulebreak_add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_rulebreak_add (QSet<quint16> *pSet, QWidget *parent = 0);
    ~Dialog_rulebreak_add();

signals:
    void send_MSG_of_rulebreak(record_rulebreak record);    //发送记录信息

private slots: 
    void on_pushButton_ok_clicked();    //接受

    void on_pushButton_cancel_clicked();    //拒绝

private:
    Ui::Dialog_rulebreak_add *ui;

    QSet<quint16> *point_to_set_of_dorm_numbers;
};

#endif // DIALOG_RULEBREAK_ADD_H
