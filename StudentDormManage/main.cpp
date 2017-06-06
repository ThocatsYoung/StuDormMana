
#include "read_from_file.h"

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "people.h"
#include "room.h"
#include "dormlistmodel.h"

#include "dialog_login.h"
#include "mainwindow_data_manager.h"

#include <QSplashScreen>

//界面美化为了省事代码上网找的
//以下宏定义来自网络（一去丶二三里）
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))

class CommonHelper
{
//用于加载qss文件，这一部分代码来自网络
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        if (!qss.exists())
        {//界面美化文件不存在时返回
            return;
        }
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
        return;
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CommonHelper::setStyle("style.qss");    //该行代码来自网络

    student::Init_of_Xueyuan_and_BanJi();
    //初始化静态student类数据成员用于与班级、学院编号对应


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


