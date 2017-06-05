#ifndef DIALOG_DORM_EDIT_H
#define DIALOG_DORM_EDIT_H

#include <QDialog>
#include <QMessageBox>
#include "dormlistmodel.h"
#include "room.h"

namespace Ui {
class Dialog_Dorm_Edit;
}

class Dialog_Dorm_Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Dorm_Edit(int type, dorm *d = 0,
                              QWidget *parent = 0);
    ~Dialog_Dorm_Edit();


    void for_add_dorm();    //用于添加宿舍
    void for_edit_dorm();   //用于修改宿舍

signals:

    void send_new_dorm_info(dorm newDorm);  //发送新宿舍信息

private slots:
    void on_pushButton_ok_clicked();    //ok

    void on_pushButton_cancel_clicked();    //cancel

private:
    Ui::Dialog_Dorm_Edit *ui;

    dorm *edit_dorm;    //被编辑的宿舍
    int edit_type;  //编辑类型，0为添加，1为修改
};

#endif // DIALOG_DORM_EDIT_H
