#ifndef STUDENT_INFORMATION_EDIT_DIALOG_H
#define STUDENT_INFORMATION_EDIT_DIALOG_H

#include <QDialog>

namespace Ui {
class student_information_edit_Dialog;
}

class student_information_edit_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit student_information_edit_Dialog(QWidget *parent = 0);
    ~student_information_edit_Dialog();

private:
    Ui::student_information_edit_Dialog *ui;
};

#endif // STUDENT_INFORMATION_EDIT_DIALOG_H
