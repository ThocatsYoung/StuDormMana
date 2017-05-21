#include "student_information_edit_dialog.h"
#include "ui_student_information_edit_dialog.h"

student_information_edit_Dialog::student_information_edit_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_information_edit_Dialog)
{
    ui->setupUi(this);
}

student_information_edit_Dialog::~student_information_edit_Dialog()
{
    delete ui;
}
