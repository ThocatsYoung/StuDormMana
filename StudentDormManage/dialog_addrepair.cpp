#include "dialog_addrepair.h"
#include "ui_dialog_addrepair.h"

Dialog_addrepair::Dialog_addrepair(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_addrepair)
{
    ui->setupUi(this);
    this->setWindowTitle("添加维修记录");

    ui->lineEdit_dorm->setFocusPolicy(Qt::NoFocus);

    ui->repair_dateEdit->setDate(QDate::currentDate());  //输入日期
}

Dialog_addrepair::~Dialog_addrepair()
{
    delete ui;
}

void Dialog_addrepair::edit_dorm_num(QString Dorm_num)
{
    ui->lineEdit_dorm->setText(Dorm_num);
}


void Dialog_addrepair::on_buttonBox_accepted()
{
    if(ui->lineEdit_dorm->text().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("宿舍号不能为空"));
        return;
    }

    if(ui->textEdit_case->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("报修事项不能为空"));
        return;
    }

    QString Dorm_num = ui->lineEdit_dorm->text();
    QString Repair_case = ui->textEdit_case->toPlainText();
    QDate Date = ui->repair_dateEdit->date();
    dorm_repair new_dorm_repair(Dorm_num, Repair_case, Date);
    emit send_MSG_of_repair(new_dorm_repair);
}
