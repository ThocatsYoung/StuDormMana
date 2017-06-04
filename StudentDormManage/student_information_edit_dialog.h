#ifndef STUDENT_INFORMATION_EDIT_DIALOG_H
#define STUDENT_INFORMATION_EDIT_DIALOG_H

#include "read_from_file.h"

#include <QDialog>
#include <QCompleter>
#include <QComboBox>

#include "people.h"
#include "room.h"

#define TEST_OF_DIALOG 1

namespace Ui {
class student_information_edit_Dialog;
}

class student_information_edit_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit student_information_edit_Dialog(int type, dorm *pDorm,
                                             student *pStudent = 0,
                                             QWidget *parent = 0);
    ~student_information_edit_Dialog();

    //用于根据 edit_type 初始化界面状态
    void for_add();
    void for_edit();

signals:
    void send_student_info(student stu_info);   //发送学生信息

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

    void change_content_of_combobox_banji(int index);   //根据学院框下标改变班级框数据

private:
    Ui::student_information_edit_Dialog *ui;
    int edit_type;  //修改类型 0为添加，1为修改
    student *edit_student;  //待编辑学生
    dorm *edit_dorm;    //待添加学生的宿舍
};

#endif // STUDENT_INFORMATION_EDIT_DIALOG_H
