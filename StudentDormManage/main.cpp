
#include "read_from_file.h"

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "people.h"
#include "room.h"
#include "dormlistmodel.h"

#include "dialog_login.h"
#include "mainwindow_data_manager.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    student::Init_of_Xueyuan_and_BanJi();


    //登录
    Dialog_Login login;
    if(login.exec() != QDialog::Accepted)
    {
        return 0;
    }
    //登陆后将改变 静态成员数据 用户名 user_Name


    //创建宿舍管理主窗口
    if(Dialog_Login::login_type == 0)   //宿管登录
    {
        MainWindow w(Dialog_Login::user_Name);
        w.setFixedSize(1090, 660);
        w.setWindowTitle("学生宿舍管理系统--宿舍管理员界面");

        //显示窗口
        w.show();
        return a.exec();

    }else{
        //创建住宿数据管理员界面
        if(Dialog_Login::login_type == 1)
        {
            MainWindow_data_manager d(Dialog_Login::user_Name);
            d.setFixedSize(1000, 530);
            d.setWindowTitle("学生宿舍管理系统--住宿数据管理员界面");
            d.show();
            return a.exec();
        }
        else
        {
            warning_message_box("登录信息错误");
            return 0;
        }
    }
    return 0;
}


