#include "dialog_wailairen_add.h"
#include "ui_dialog_wailairen_add.h"
//改动
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

dialog_wailairen_add::~dialog_wailairen_add()
{
    delete ui;
}

void dialog_wailairen_add::on_buttonBox_accepted()
{
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
    QString Name = ui->lineEdit_name->text();
    QString IdNumber =ui->lineEdit_id->text();
    QString Contact=ui->lineEdit_3->text();
    quint16 msex = ui->comboBox->currentIndex();
    QDateTime date = ui->dateTimeEdit->dateTime();
    outsider new_record(Name, msex,IdNumber, Contact,date);
    emit send_MSG_of_wailairen(new_record);
    this->accept();

}

void dialog_wailairen_add::on_buttonBox_rejected()
{
    this->reject();
}
