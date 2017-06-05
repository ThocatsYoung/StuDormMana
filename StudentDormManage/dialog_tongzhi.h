#ifndef DIALOG_TONGZHI_H
#define DIALOG_TONGZHI_H

#include "read_from_file.h"
#include <QDialog>

namespace Ui {
class Dialog_tongzhi;
}

class Dialog_tongzhi : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_tongzhi(QWidget *parent = 0);
    ~Dialog_tongzhi();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_tongzhi *ui;
};

#endif // DIALOG_TONGZHI_H
