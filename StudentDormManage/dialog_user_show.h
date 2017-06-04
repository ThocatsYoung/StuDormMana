#ifndef DIALOG_USER_SHOW_H
#define DIALOG_USER_SHOW_H

#include "read_from_file.h"
#include <QDialog>
#include <QMap>

#include "dialog_user_info.h"

namespace Ui {
class Dialog_user_show;
}

class Dialog_user_show : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_user_show(int type, QMap<QString, QString> *point_to_map,
                              QWidget *parent = 0);
    ~Dialog_user_show();

    //用于根据 edit_type 初始化界面状态
    void for_load();
    void for_add_and_delete();

signals:
    void send_building_info(QString s);

private slots:
    void add_user(QString user, QString mima);
    void on_pushButton_add_user_clicked();

    void on_pushButton_delete_data_clicked();

    void on_pushButton_load_data_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::Dialog_user_show *ui;
    int edit_type;  //0为load, 1为add_and_delete
    QMap<QString, QString> *point_to_map_dorm_manager;
};

#endif // DIALOG_USER_SHOW_H
