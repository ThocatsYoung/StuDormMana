#ifndef DIALOG_ADDREPAIR_H
#define DIALOG_ADDREPAIR_H

#include <QDialog>
#include <QMessageBox>
#include "dorm_repair.h"
#include "read_from_file.h"

namespace Ui {
class Dialog_addrepair;
}

class Dialog_addrepair : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_addrepair(QWidget *parent = 0);
    ~Dialog_addrepair();

    void edit_dorm_num(QString Dorm_num);

signals:
    void send_MSG_of_repair(dorm_repair Dorm_repair);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_addrepair *ui;
};

#endif // DIALOG_ADDREPAIR_H
