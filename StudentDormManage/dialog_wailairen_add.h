#ifndef DIALOG_WAILAIREN_ADD_H
#define DIALOG_WAILAIREN_ADD_H
#include <QDialog>
#include <QMessageBox>
#include "read_from_file.h"
#include <QWidget>
#include"wailairen.h"
#include"people.h"

namespace Ui {
class dialog_wailairen_add;
}

class dialog_wailairen_add : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_wailairen_add(QWidget *parent = 0);
    ~dialog_wailairen_add();
signals:
    void send_MSG_of_wailairen(outsider record);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::dialog_wailairen_add *ui;
};

#endif // DIALOG_WAILAIREN_ADD_H
