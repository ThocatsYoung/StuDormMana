#include "dialog_addgoods.h"
#include "ui_dialog_addgoods.h"

Dialog_addgoods::Dialog_addgoods(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_addgoods)
{
    ui->setupUi(this);
    this->setWindowTitle("添加物品");

    QRegExp add_goodsnumber("[0-9]{25}");
    QValidator *add_number = new QRegExpValidator(add_goodsnumber, ui->lineEdit_2_add_goodsnumber);
    ui->lineEdit_2_add_goodsnumber->setValidator(add_number);

}

Dialog_addgoods::~Dialog_addgoods()
{
    delete ui;
}

void Dialog_addgoods::on_buttonBox_accepted()
{
    if(ui->lineEdit_add_goods->text().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"),tr("物品名不能为空"));
        return;
    }

    if(ui->lineEdit_2_add_goodsnumber == 0)
    {
        QMessageBox::warning(this, tr("警告"), tr("物品数量不能为0"));
        return;
    }

    QString Goodsname = ui->lineEdit_add_goods->text();
    qint32 Total = ui->lineEdit_2_add_goodsnumber->text().toInt();
    qint32 Nownumber = Total;
    goods Goods(Goodsname, Total, Nownumber);
    emit send_MSG_of_goods(Goods);
}
