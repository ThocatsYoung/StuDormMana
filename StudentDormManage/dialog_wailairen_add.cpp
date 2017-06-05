#include "dialog_wailairen_add.h"
#include "ui_dialog_wailairen_add.h"


//添加外来人员的对话框
dialog_wailairen_add::dialog_wailairen_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_wailairen_add)
{
    ui->setupUi(this);

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    //设置补全框
    foreach(QString s, outsider::sex_things)
    {
        ui->comboBox->addItem(s,outsider::sex_things.indexOf(s));
    }
}


//析构函数
dialog_wailairen_add::~dialog_wailairen_add()
{
    delete ui;
}


void dialog_wailairen_add::on_buttonBox_accepted()//添加外来人员信息按钮
{
    //判断输入是否合法
    if(ui->lineEdit_name->text().isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),tr("姓名不可为空"));
        return;
    }
    if(ui->lineEdit_id->text().isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),tr("证件号不可为空"));
        return;
    }
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),tr("联系方式不可为空"));
        return;
    }
    //获取输入的数据
    QString Name = ui->lineEdit_name->text();     //姓名
    QString IdNumber =ui->lineEdit_id->text();     //ID
    QString Contact=ui->lineEdit_3->text();       //联系方式
    quint16 msex = ui->comboBox->currentIndex();  //性别
    QDateTime date = ui->dateTimeEdit->dateTime();//时间
    outsider new_record(Name, msex,IdNumber, Contact,date);
    emit send_MSG_of_wailairen(new_record);   //发送信息修改的信号
    this->accept();

}

//取消添加
void dialog_wailairen_add::on_buttonBox_rejected()
{
    this->reject();
}
