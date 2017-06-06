#ifndef DIALOG_ADDGOODS_H
#define DIALOG_ADDGOODS_H

#include <QDialog>
#include <QMessageBox>
#include "goods.h"
#include "read_from_file.h"

namespace Ui {
class Dialog_addgoods;
}

class Dialog_addgoods : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_addgoods(QWidget *parent = 0);
    ~Dialog_addgoods();

signals:
    void send_MSG_of_goods(goods Goods);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_addgoods *ui;
};

#endif // DIALOG_ADDGOODS_H
