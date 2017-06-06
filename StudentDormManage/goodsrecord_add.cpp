#include "goodsrecord_add.h"
#include "ui_goodsrecord_add.h"

goodsrecord_add::goodsrecord_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodsrecord_add)
{
    ui->setupUi(this);


    ui->lineEdit_nownumber->setFocusPolicy(Qt::NoFocus);  //余量不可编辑
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);   //物品名不可编辑
    QRegExp regx1("[0-9]{11}");   //限制联系输入为数字
    QRegExp regx2("[1-9][0-9]{10}");  //限制借出输入为数字
    QValidator *edit_phone = new QRegExpValidator(regx1, ui->phone_lineEdit_3);
    ui->phone_lineEdit_3->setValidator(edit_phone);
    QValidator *edit_use = new QRegExpValidator(regx2, ui->usenumber_lineEdit_4);
    ui->usenumber_lineEdit_4->setValidator(edit_use);

    ui->borrow_dateEdit->setDate(QDate::currentDate());
    ui->back_dateEdit_2->setDate(QDate::currentDate());

}

goodsrecord_add::~goodsrecord_add()
{
    delete ui;
}

void goodsrecord_add::edit_line(QString Goodsname, QString Nownumber)
{
    ui->lineEdit->setText(Goodsname);
    ui->lineEdit_nownumber->setText(Nownumber);

}

int goodsrecord_add::get_usenumber()
{
    return ui->usenumber_lineEdit_4->text().toInt();
}


void goodsrecord_add::on_buttonBox_accepted()
{
    if(ui->lineEdit_nownumber == 0)
    {
        QMessageBox::warning(this, tr("抱歉"), tr("该物品已借空"));
        return;
    }

    if((ui->manname_lineEdit_2->text().isEmpty()) ||
            ui->phone_lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("借用人或联系电话不能为空"));
        return;
    }

    if(ui->usenumber_lineEdit_4->text() >= ui->lineEdit_nownumber->text())
    {
        QMessageBox::warning(this, tr("警告"), tr("借用数量超过剩余数量"));
        return;
    }

    QString Goodsname = ui->lineEdit->text();
    QString Manname = ui->manname_lineEdit_2->text();
    QString Phonenumber = ui->phone_lineEdit_3->text();
    qint32 Usenumber = ui->usenumber_lineEdit_4->text().toInt();
    QDate Borrowdate = ui->borrow_dateEdit->date();
    QDate Backdate = ui->back_dateEdit_2->date();
    goods_record new_goodsrecord(Goodsname, Manname, Phonenumber, Usenumber, Borrowdate, Backdate);
    emit send_MSG_goodsrecord(new_goodsrecord);
    this->accept();

}
