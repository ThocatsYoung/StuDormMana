#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QDataStream>

#include <QMap>

#include "read_from_file.h"

namespace Ui {
class Dialog_Login;
}

class Dialog_Login : public QDialog
{
    Q_OBJECT

public:
    static int login_type;  //  登录类型，0为宿舍管理员，1为数据管理员
    explicit Dialog_Login(QString path_data, QString path_dorm, QWidget *parent = 0);
    ~Dialog_Login();

    void clean_mima_edit();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog_Login *ui;
    QMap<QString, QString> map_data_manager;
    QMap<QString, QString> map_dorm_manager;
};

#endif // DIALOG_LOGIN_H
