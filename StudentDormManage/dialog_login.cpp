#include "dialog_login.h"
#include "ui_dialog_login.h"

Dialog_Login::Dialog_Login(QString path_data, QString path_dorm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Login)
{
    ui->setupUi(this);
    this->setWindowTitle("学生宿舍管理系统--登录");
    ui->lineEdit_user_name->setFocus();

    //初始化登录人员数据(文件读写)
    read_file_to_container(path_data, map_data_manager);
    read_file_to_container(path_dorm, map_dorm_manager);


#if 1
    //测试用登陆数据
    map_data_manager.insert("root","root123");
    map_dorm_manager.insert("c12","123456");

#endif
}

int Dialog_Login::login_type = 0;

Dialog_Login::~Dialog_Login()
{

    delete ui;
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
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码不可为空"));
        clean_mima_edit();
        return;
    }
    //数据管理员登录
    if (ui->radioButton_data_manager->isChecked())
    {
        if(map_data_manager.contains(userid) &&
                 mima == map_data_manager.value(userid))
        {
            login_type = 1;
            qDebug() << QString("%1").arg(login_type);
            this->accept();
            QMessageBox::information(this,tr("信息"),tr("你已成功登录！"));
            return;
        }else{
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误"));
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
            qDebug() << QString("%1").arg(login_type);
            this->accept();
            QMessageBox::information(this,tr("信息"),tr("你已成功登录！"));
            return;
        }else{
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误"));
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
