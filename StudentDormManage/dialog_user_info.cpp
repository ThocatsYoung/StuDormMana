#include "dialog_user_info.h"
#include "ui_dialog_user_info.h"

Dialog_user_info::Dialog_user_info(int type, QWidget *parent,
                                   QString value_user, QString value_mima) :
    edit_type(type),
    user_id(value_user), mima(value_mima),
    QDialog(parent),
    ui(new Ui::Dialog_user_info)
{
    ui->setupUi(this);

#if DEBUG_TEST
    qDebug() << "accepted";
    qDebug() << user_id;
    qDebug() << mima;
#endif

    if (edit_type == 0){
        for_add();
    }else{
        for_change_mima();
    }
}


Dialog_user_info::~Dialog_user_info()
{
    delete ui;
}

bool Dialog_user_info::check_if_empty()
{
    if (ui->lineEdit_user_id->text().isEmpty()){
        warning_message_box("用户名不可为空！");
        ui->lineEdit_user_id->setFocus();
        return true;
    }

    if (ui->lineEdit_mima_first->text().isEmpty() ||
            ui->lineEdit_mima_second->text().isEmpty()){
        warning_message_box("输入密码不可为空!");
        ui->lineEdit_mima_first->setFocus();
        return true;
    }
    return false;
}

void Dialog_user_info::for_add()
{
    this->setWindowTitle("添加用户");

    ui->label_text_mima_1->setText("输入密码");
    ui->label_tex_mima_2->setText("再次输入密码");

    ui->lineEdit_user_id->setEnabled(true);
    ui->lineEdit_user_id->clear();
    ui->lineEdit_user_id->setFocus();
}

void Dialog_user_info::for_change_mima()
{
    this->setWindowTitle("修改密码");

    ui->label_text_mima_1->setText("输入旧密码");
    ui->label_tex_mima_2->setText("输入新密码");

    ui->lineEdit_user_id->setEnabled(false);
    ui->lineEdit_user_id->setText(user_id);

    ui->lineEdit_mima_first->setFocus();
}

void Dialog_user_info::on_pushButton_ok_clicked()
{
    if (check_if_empty()){
        return;
    }
    QString mima_1 = ui->lineEdit_mima_first->text();
    QString mima_2 = ui->lineEdit_mima_second->text();

    if (edit_type == 0){
        //添加用户 type == 0
        user_id = ui->lineEdit_user_id->text();
        if (mima_1.length() < 6){
            warning_message_box("密码长度至少应为6位!");
            ui->lineEdit_mima_first->clear();
            ui->lineEdit_mima_second->clear();
            ui->lineEdit_mima_first->setFocus();
            return;
        }
        if (mima_1 != mima_2){
            warning_message_box("两次输入密码不一致!");
            ui->lineEdit_mima_second->clear();
            ui->lineEdit_mima_second->setFocus();
            return;
        }
        mima = mima_1;

        switch( QMessageBox::information(this,tr("提示"),
                                         tr("确定添加该用户？"),
                                         tr("确定"), tr("取消"),0,1))
        {
        case 0:
            emit new_user(user_id, mima);   //发出新用户数据
            this->accept();
            break;
        case 1:
        default:
            break;
        }
        return;

    }else{
        //修改密码 type == 1
        if (mima_1 != mima){
            warning_message_box("密码错误");
            ui->lineEdit_mima_first->clear();
            ui->lineEdit_mima_second->clear();
            ui->lineEdit_mima_first->setFocus();
            return;
        }
        if (mima_2.length() < 6){
            warning_message_box("新密码长度至少应为6位!");
            ui->lineEdit_mima_second->clear();
            ui->lineEdit_mima_second->setFocus();
            return;
        }
        mima = mima_2;
        emit changed_mima(mima);    //发出新密码数据
        information_message_box("密码修改完成");
        this->accept();
        return;
    }
}

void Dialog_user_info::on_pushButton_cancel_clicked()
{
    this->reject();
}
