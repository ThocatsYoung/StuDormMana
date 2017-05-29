#ifndef DIALOG_RULEBREAK_ADD_H
#define DIALOG_RULEBREAK_ADD_H

#include <QDialog>
#include <QMessageBox>
#include "formforrulebreakrecord.h"


namespace Ui {
class Dialog_rulebreak_add;
}

class Dialog_rulebreak_add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_rulebreak_add(QWidget *parent = 0);
    ~Dialog_rulebreak_add();

signals:
    void send_MSG_of_rulebreak(record_rulebreak record);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_rulebreak_add *ui;
};

#endif // DIALOG_RULEBREAK_ADD_H
