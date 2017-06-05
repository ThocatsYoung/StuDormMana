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
    static int login_type;  //登录类型，0为宿舍管理员，1为数据管理员  在main函数中以此建立相应的界面
    static QString user_Name;   //登录用户名，初始为空    main函数中以此作为界面建立参数
    explicit Dialog_Login(QWidget *parent = 0);
    ~Dialog_Login();

    void save_login_data(); //保存数据...其实不是很有必要
    void clean_mima_edit(); //清空密码栏

private slots:

    void on_pushButton_login_clicked();     //登录

    void on_pushButton_cancel_clicked();    //离开

private:
    Ui::Dialog_Login *ui;

    //该对话框直接从文件读取用户数据以供查询
    QMap<QString, QString> map_data_manager;
    QMap<QString, QString> map_dorm_manager;
};

#endif // DIALOG_LOGIN_H
