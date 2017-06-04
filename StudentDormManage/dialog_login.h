#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H


#include "read_from_file.h"
#include <QDialog>
#include <QMessageBox>

#include <QMap>
#include <QString>



namespace Ui {
class Dialog_Login;
}

class Dialog_Login : public QDialog
{
    Q_OBJECT

public:
    static int login_type;  //登录类型，0为宿舍管理员，1为数据管理员
    static QString user_Name;   //登录用户名，初始为空
    explicit Dialog_Login(QWidget *parent = 0);
    ~Dialog_Login();

    void save_login_data();
    void clean_mima_edit(); //清空密码栏

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_Login *ui;
    QMap<QString, QString> map_data_manager;
    QMap<QString, QString> map_dorm_manager;
};

#endif // DIALOG_LOGIN_H
