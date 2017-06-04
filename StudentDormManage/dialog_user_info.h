#ifndef DIALOG_USER_INFO_H
#define DIALOG_USER_INFO_H

#include "read_from_file.h"
#include <QDialog>

namespace Ui {
class Dialog_user_info;
}

class Dialog_user_info : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog_user_info(int type, QWidget *parent = 0,
                              QString value_user = QString(), QString value_mima = QString());
    ~Dialog_user_info();

    bool check_if_empty();  //有编辑栏为空时提醒并返回true

    //用于根据 edit_type 初始化界面状态
    void for_add();
    void for_change_mima();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();
signals:
    //发出新的或是修改后的用户、密码的QString，由连接的槽函数修改
    void new_user(QString name_of_new_user, QString mima);
    void changed_mima(QString new_mima);

private:
    Ui::Dialog_user_info *ui;

    int edit_type;  //0为添加用户，1为改密码
    QString user_id;
    QString mima;
};

#endif // DIALOG_USER_INFO_H
