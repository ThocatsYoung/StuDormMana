#include "dialog_tongzhi.h"
#include "ui_dialog_tongzhi.h"

Dialog_tongzhi::Dialog_tongzhi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_tongzhi)
{
    ui->setupUi(this);
    this->setWindowTitle("通知编辑");

    QString current_tongzhi;
    read_file_to_container(path::_of_Tongzhi, current_tongzhi);
    ui->textEdit->setText(current_tongzhi);

}

Dialog_tongzhi::~Dialog_tongzhi()
{
    delete ui;
}

void Dialog_tongzhi::on_pushButton_ok_clicked()
{
    int reply = ask_yes_or_no("确定发布通知？");
    if (reply == true)
    {
        QString tongzhi = ui->textEdit->toPlainText();
        write_container_to_file(tongzhi, path::_of_Tongzhi);
        this->accept();
        return;
    }else{
        return;
    }
}

void Dialog_tongzhi::on_pushButton_cancel_clicked()
{
    this->reject();
}
