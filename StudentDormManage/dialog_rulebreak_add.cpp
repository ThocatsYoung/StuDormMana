#include "dialog_rulebreak_add.h"
#include "ui_dialog_rulebreak_add.h"

Dialog_rulebreak_add::Dialog_rulebreak_add(QWidget *parent) :
    QDialog(parent),
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

void Dialog_rulebreak_add::on_buttonBox_accepted()
{
    if(ui->lineEdit->text().isEmpty())
    {
        warning_message_box("宿舍号不可为空");
        return;
    }

    quint16 dorm_number = ui->lineEdit->text().toInt();
    quint16 breaked_rule = ui->comboBox->currentIndex();
    QDate date = ui->dateEdit->date();
    record_rulebreak new_record(dorm_number, breaked_rule, date);
    emit send_MSG_of_rulebreak(new_record);

}
