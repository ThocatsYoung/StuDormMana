#include "dialog_rulebreak_add.h"
#include "ui_dialog_rulebreak_add.h"

Dialog_rulebreak_add::Dialog_rulebreak_add(QSet<quint16> *pSet, QWidget *parent) :
    point_to_set_of_dorm_numbers(pSet), QDialog(parent),
    ui(new Ui::Dialog_rulebreak_add)
{
    ui->setupUi(this);

    this->setWindowTitle("宿舍违纪记录添加");

    QRegExp regx1("[1-9][0-9]{0,2}");   //第一位不可为0，限制3位数
    QValidator *of_edit_dorm = new QRegExpValidator(regx1, ui->lineEdit);
    ui->lineEdit->setValidator(of_edit_dorm);

    ui->dateEdit->setDate(QDate::currentDate());


    //设置补全框
    foreach(QString s, record_rulebreak::break_rule_things)
    {
        ui->comboBox->addItem(s,record_rulebreak::break_rule_things.indexOf(s));
    }
}

Dialog_rulebreak_add::~Dialog_rulebreak_add()
{
    delete ui;
}


void Dialog_rulebreak_add::on_pushButton_ok_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        warning_message_box("宿舍号不可为空");
        return;
    }

//读取信息并构造新记录
    quint16 dorm_number = ui->lineEdit->text().toInt();
    //判断宿舍号是否存在
    if (!point_to_set_of_dorm_numbers->contains(dorm_number)){
        warning_message_box("宿舍号不存在！");
        return;
    }

    quint16 breaked_rule = ui->comboBox->currentIndex();
    QDate date = ui->dateEdit->date();
    record_rulebreak new_record(dorm_number, breaked_rule, date);

    emit send_MSG_of_rulebreak(new_record); //发送新记录

    this->accept();
}

void Dialog_rulebreak_add::on_pushButton_cancel_clicked()
{
    this->reject();
}
