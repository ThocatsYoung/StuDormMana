#include "dialog_login.h"
#include "ui_dialog_login.h"

Dialog_Login::Dialog_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Login)
{
    ui->setupUi(this);
    this->setWindowTitle("学生宿舍管理系统--登录");

    //初始化登录人员数据(文件读写)
    read_file_to_container(path_of_data_manager, map_data_manager);
    read_file_to_container(path_of_dorm_manager, map_dorm_manager);

    //默认数据用户
    if (map_data_manager.empty())
    {
#if DEBUG_TEST
        qDebug() << "have no data manager";
#endif
        map_data_manager.insert("root","root123");

    }

#if DEBUG_TEST
    //测试用登陆数据
    ui->lineEdit_user_name->setText("root");
    ui->lineEdit_mima->setText("root123");
    ui->lineEdit_user_name->setFocus();
#endif

    //当已存在宿管用户没有专属文件夹时建立
    QMapIterator<QString, QString> i(map_dorm_manager);
    while(i.hasNext()){
        create_dir_if_no_exist(i.next().key());
    }


}

//静态数据定义
int Dialog_Login::login_type = 0;
QString Dialog_Login::user_Name;


Dialog_Login::~Dialog_Login()
{
    delete ui;
}

void Dialog_Login::save_login_data()
{
#if DEBUG_TEST
    //测试用
    qDebug() << "user names";
    QMapIterator<QString,QString> i(map_data_manager);
    while(i.hasNext()){
        qDebug() << i.next().key();
    }
    QMapIterator<QString,QString> j(map_dorm_manager);
    while(j.hasNext()){
        qDebug() << j.next().key();
    }
#endif
    //写入容器
    write_container_to_file(map_data_manager,path_of_data_manager);
    write_container_to_file(map_dorm_manager,path_of_dorm_manager);
}

void Dialog_Login::clean_mima_edit()
{
    //清空密码栏
    this->ui->lineEdit_mima->clear();
    this->ui->lineEdit_mima->setFocus();
}

void Dialog_Login::on_pushButton_login_clicked()
{
    //登录
    QString userid = ui->lineEdit_user_name->text();
    QString mima = ui->lineEdit_mima->text();

    if (userid.isEmpty() || mima.isEmpty())
    {
        warning_message_box("用户名或密码不可为空");
        clean_mima_edit();
        return;
    }
    //数据管理员登录
    if (ui->radioButton_data_manager->isChecked())
    {
        if(map_data_manager.contains(userid) &&
                 mima == map_data_manager.value(userid))
        {
            login_type = 1; //调整静态数据值
            qDebug() << QString("%1").arg(login_type);
            this->accept();
            information_message_box("你已成功登录！");
            user_Name = userid;
            return;
        }else{
            warning_message_box("用户名或密码错误");
            clean_mima_edit();
            return;
        }
    }
    //宿舍管理员登录
    if (ui->radioButton_dorm_manager->isChecked())
    {
        if(map_dorm_manager.contains(userid) &&
                 mima == map_dorm_manager.value(userid))
        {
            login_type = 0;
#if DEBUG_TEST
            qDebug() << "login type";
            qDebug() << QString("%1").arg(login_type);
#endif
            this->accept();
            save_login_data();
            information_message_box("你已成功登录！");
            user_Name = userid;
            return;
        }else{
            warning_message_box("用户名或密码错误");
            clean_mima_edit();
            return;
        }
    }
    return;
}


void Dialog_Login::on_pushButton_cancel_clicked()
{
    this->close();
}
