#include "dialog_dorm_edit.h"
#include "ui_dialog_dorm_edit.h"

Dialog_Dorm_Edit::Dialog_Dorm_Edit(int type, dorm *d,
                                   QWidget *parent) :
    edit_type(type),
    edit_dorm(d),
    QDialog(parent),
    ui(new Ui::Dialog_Dorm_Edit)
{
    ui->setupUi(this);
    this->setWhatsThis("宿舍号为3位整数\n宿舍最大人数最多为20人");

    QDoubleValidator *of_edit_fee= new QDoubleValidator (0, 100, 1, this);


    ui->lineEdit_elec_fee->setValidator(of_edit_fee);
    ui->lineEdit_water_fee->setValidator(of_edit_fee);

    switch(edit_type){
    case 0:
        for_add_dorm();break;
    case 1:
        for_edit_dorm();break;
    default:
        break;
    }

}

Dialog_Dorm_Edit::~Dialog_Dorm_Edit()
{
    delete ui;
}

void Dialog_Dorm_Edit::for_add_dorm()
{
    this->setWindowTitle("添加宿舍");
    ui->pushButton_ok->setText("添加宿舍");

    ui->lineEdit_dorm->setEnabled(true);
    ui->lineEdit_dorm->setValidator(new QIntValidator(100, 999, this));

    ui->lineEdit_max->setEnabled(true);
    ui->lineEdit_max->setValidator(new QIntValidator(0, 20, this));

    ui->lineEdit_elec_fee->setText("0.0");
    ui->lineEdit_elec_fee->setEnabled(false);
    ui->lineEdit_water_fee->setText("0.0");
    ui->lineEdit_water_fee->setEnabled(false);

    ui->lineEdit_dorm->setFocus();
}

void Dialog_Dorm_Edit::for_edit_dorm()
{
    //设置初始值
    this->setWindowTitle("修改信宿舍息");
    ui->pushButton_ok->setText("修改");

    ui->lineEdit_dorm->setEnabled(false);
    ui->lineEdit_dorm->setText(QString("%1").arg(edit_dorm->GetDormNumber()));
    ui->lineEdit_dorm->setValidator(new QIntValidator(100, 999, this));

    ui->lineEdit_max->setEnabled(true);
    ui->lineEdit_max->setText(QString("%1").arg(edit_dorm->GetMaxNumber()));
    ui->lineEdit_max->setValidator(new QIntValidator(0, 20, this));

    ui->lineEdit_elec_fee->setEnabled(true);
    ui->lineEdit_water_fee->setEnabled(true);
    ui->lineEdit_elec_fee->setText(QString("%1").arg(edit_dorm->GetElecFee()));
    ui->lineEdit_water_fee->setText(QString("%1").arg(edit_dorm->GetWaterFee()));

    //限制输入
    QDoubleValidator *of_edit_fee= new QDoubleValidator (0, 100, 2, this);
    ui->lineEdit_elec_fee->setValidator(of_edit_fee);
    ui->lineEdit_water_fee->setValidator(of_edit_fee);
}

void Dialog_Dorm_Edit::on_pushButton_ok_clicked()
{

    QString dorm_number_text = ui->lineEdit_dorm->text();
    QString max_number_text = ui->lineEdit_max->text();
    QString wfee_text = ui->lineEdit_water_fee->text();
    QString efee_text = ui->lineEdit_elec_fee->text();



    //数据检验(未完成)
    if (dorm_number_text.isEmpty() || max_number_text.isEmpty()
            || wfee_text.isEmpty() || efee_text.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"),tr("编辑框不可为空"));
        return;
    }
    if (dorm_number_text.count() < 3)
    {
        QMessageBox::warning(this,tr("警告"),tr("宿舍号须为3位数字"));
        return;
    }

    quint16 dorm_number = dorm_number_text.toInt();
    quint16 max_number = max_number_text.toInt();

    if (edit_type == 1){
        quint16 now_number = edit_dorm->GetNowNumber();
        if (max_number < now_number)
        {
            warning_message_box("宿舍最大居住人员数小于当前居住人数");
            return;
        }
    }


    //确认修改数据
    QString ask;
    if (edit_type == 0){
        ask = "确定添加该宿舍数据？";
    }else{
        ask = "确定编辑宿舍数据？";
    }
    int reply = QMessageBox::question(this,tr("询问"),ask,
                          QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    //进行数据修改


    double wfee = wfee_text.toDouble();
    double efee = efee_text.toDouble();

    if (edit_type == 0){
        dorm new_dorm(dorm_number, max_number);
        emit this->send_new_dorm_info(new_dorm);    //发出新宿舍数据
        this->accept();
        return;
    }
    if (edit_type == 1){
        //改变宿舍数据
        edit_dorm->setMaxNumber(max_number);
        edit_dorm->SetElecFee(efee);
        edit_dorm->SetWaterFee(wfee);
        this->accept();
        return;
    }
}


void Dialog_Dorm_Edit::on_pushButton_cancel_clicked()
{
    this->reject();
}
