#ifndef DIALOG_WAILAIREN_ADD_H
#define DIALOG_WAILAIREN_ADD_H
#include <QDialog>
#include <QMessageBox>
#include "read_from_file.h"
#include <QWidget>
#include"wailairen.h"
#include"people.h"



//外来人员信息添加界面
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
    void send_MSG_of_wailairen(outsider record);//发送外来人员信息修改的信号

private slots:
    void on_buttonBox_accepted();         //确认添加信息
    void on_buttonBox_rejected();         //取消添加信息

private:
    Ui::dialog_wailairen_add *ui;
};

#endif // DIALOG_WAILAIREN_ADD_H
