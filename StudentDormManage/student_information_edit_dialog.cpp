#include "student_information_edit_dialog.h"
#include "ui_student_information_edit_dialog.h"

student_information_edit_Dialog::student_information_edit_Dialog(int type,
                                                                 dorm *pDorm,
                                                                 student *pStudent,QWidget *parent) :
    edit_type(type), edit_dorm(pDorm),
    edit_student(pStudent), QDialog(parent),
    ui(new Ui::student_information_edit_Dialog)
{
    ui->setupUi(this);
//初始化

    //身份证及学号编辑栏设置
    QRegExp regx_ids("[1-9][0-9]{0,25}");   //第一位不可为0，至多26位，用于多位数字输入
    QValidator *of_edit_ids = new QRegExpValidator(regx_ids, this);

    ui->lineEdit_student_id->setValidator(of_edit_ids);
    ui->lineEdit_id_number->setValidator(of_edit_ids);

    //学院补全框
    ui->comboBox_XueYuan->addItems(student::list_of_XueYuan);
    ui->comboBox_XueYuan->setCurrentIndex(0);


    //班级补全框
    ui->comboBox_BanJi->addItems(student::lists_of_BanJi.at(0));
    connect(ui->comboBox_XueYuan, SIGNAL(currentIndexChanged(int)),
            this, SLOT(change_content_of_combobox_banji(int)));


    //性别补全框
    ui->comboBox_Sex->addItems(people::text_of_sex);
    ui->comboBox_Sex->setCurrentIndex(1);

    if (edit_type == 0){
        for_add();
    }else{
        for_edit();
    }
}

student_information_edit_Dialog::~student_information_edit_Dialog()
{
    edit_student = NULL;
    edit_dorm = NULL;
    delete ui;
}

void student_information_edit_Dialog::for_add()
{
    this->setWindowTitle("添加学生");
    ui->lineEdit_Name->setFocus();
    ui->pushButton_ok->setText("添加");
    ui->lineEdit_student_id->setEnabled(true);
}

void student_information_edit_Dialog::for_edit()
{
    this->setWindowTitle("修改学生信息");
    ui->pushButton_ok->setText("修改");
    ui->lineEdit_student_id->setEnabled(false);

    //初始化各输入框为待编辑学生信息
    ui->lineEdit_Name->setText(edit_student->GetName());
    ui->lineEdit_contact->setText(edit_student->GetContact());
    ui->lineEdit_id_number->setText(edit_student->GetIdNumber());
    ui->lineEdit_student_id->setText(edit_student->GetStudentId());

    ui->comboBox_Sex->setCurrentIndex(edit_student->GetSexuality());

    //班级，学院编号越界判定，越界时设为有效的最大数
    int index_of_xueyuan = edit_student->GetXueYuan();
    if (index_of_xueyuan >= ui->comboBox_XueYuan->count()){
        index_of_xueyuan = ui->comboBox_XueYuan->count() - 1;
    }
    ui->comboBox_XueYuan->setCurrentIndex(index_of_xueyuan);

    int index_of_banji = edit_student->GetBanJi();
    if (index_of_banji >= ui->comboBox_BanJi->count()){
        index_of_banji = ui->comboBox_BanJi->count() - 1;
    }

    ui->comboBox_BanJi->setCurrentIndex(index_of_banji);
}

void student_information_edit_Dialog::on_pushButton_cancel_clicked()
{
    this->reject();
}

void student_information_edit_Dialog::on_pushButton_ok_clicked()
{
    //编辑框不可为空
    if (ui->lineEdit_Name->text().isEmpty()
            || ui->lineEdit_id_number->text().isEmpty()
            || ui->lineEdit_student_id->text().isEmpty()
            || ui->lineEdit_contact->text().isEmpty())
    {
        warning_message_box("编辑框不可为空");
        return;
    }

    //确认修改数据
    QString ask;
    if (edit_type == 0){
        ask = "确定添加该学生数据？";
    }else{
        ask = "确定编辑学生数据？";
    }
    int reply = QMessageBox::question(this,tr("询问"),ask,
                          QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    //构造学生对象
    student new_stu;

    new_stu.SetDormNumber(edit_dorm->GetDormNumber());

    new_stu.SetName(ui->lineEdit_Name->text());
    new_stu.SetContact(ui->lineEdit_contact->text());

    new_stu.SetStudentId(ui->lineEdit_student_id->text());
    new_stu.SetIdNumber(ui->lineEdit_id_number->text());

    new_stu.SetSexuality(ui->comboBox_Sex->currentIndex());
    new_stu.SetBanji(ui->comboBox_BanJi->currentIndex());
    new_stu.SetXueYuan(ui->comboBox_XueYuan->currentIndex());

    if (edit_type == 0)
    {
        emit this->send_student_info(new_stu);
    }else{
        //直接修改学生属性
        (*edit_student) = new_stu;
    }
    this->accept();
    return;
}

void student_information_edit_Dialog::change_content_of_combobox_banji(int index)
{
    ui->comboBox_BanJi->clear();
    ui->comboBox_BanJi->addItems(student::lists_of_BanJi.at(index));
}
