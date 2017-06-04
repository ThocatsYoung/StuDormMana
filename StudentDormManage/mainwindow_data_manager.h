#ifndef MAINWINDOW_DATA_MANAGER_H
#define MAINWINDOW_DATA_MANAGER_H

#include <QMainWindow>
#include <QFormLayout>
#include <QDialogButtonBox>

#include "read_from_file.h"
#include "people.h"
#include "room.h"
#include "dormlistmodel.h"
#include "studentlistmodel.h"

#include "student_information_edit_dialog.h"
#include "dialog_dorm_edit.h"
#include "dialog_user_show.h"
#include "dialog_user_info.h"

namespace Ui {
class MainWindow_data_manager;
}

class MainWindow_data_manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_data_manager(QString user,
                                     QWidget *parent = 0);
    ~MainWindow_data_manager();


    void setModel_dorm(DormListModel *value);
    void setModel_student(StudentListModel *value);

//初始化数据结构
    void init_user_data();
    void init_list_of_dorm();
    void init_map_find_by_student_id();
    void init_set_of_dorm_number();

//保存宿舍信息
    void save_user_data_to_file();
    void save_dorm_data_to_file();

    QString getDorm_building_name() const;


signals:
    void send_message_for_dorm_find(QString str);
    void send_point_of_student_list_to_model(QList<student> *p);

private slots:
    void solt_for_action_edit_mima();   //修改密码动作触发

    void slot_for_action_manage_users();    //帐户管理动作触发

    void edit_current_mima(QString mima);   //修改当前帐户密码

    void setDorm_building_name(const QString &value);   //改变所存储的宿舍楼信息（从一栋换到另一栋）

    void add_new_dorm_to_list(dorm value);

    void on_pushButton_find_by_stuid_clicked();

    void on_pushButton_to_dorm_clicked();   //查找宿舍楼

    void on_pushButton_add_dorm_clicked();  //添加宿舍

    void on_pushButton_show_student_clicked();  //显示学生详细信息

    void change_dorm_information(QModelIndex sended_index); //改变宿舍信息标签值

    void on_pushButton_edit_dorm_clicked(); //修改宿舍信息

    void on_pushButton_delete_dorm_clicked();   //删除宿舍

    void on_pushButton_add_student_clicked();   //添加宿舍

    void find_dorm_in_listview_dorm(QString dorm_number);   //查找宿舍并跳转

    void add_student_to_current_dorm(student new_student);  //添加学生信息

    void on_pushButton_edit_student_clicked();      //修改学生信息

    void on_pushButton_delete_student_clicked();    //删除学生信息

    void on_commandLinkButton_clicked();    //进入载入数据界面 按钮名字忘记改了(注意)

private:
    Ui::MainWindow_data_manager *ui;

    QString user_name;  //用户名

    QString dorm_building_name;  //显示数据的宿舍楼名称

    QList<dorm> m_list_of_dorm;    //指向宿舍链表
    QMap<QString, student*> m_map_find_by_student_id;  //以学号索引学生地址的map
    QSet<quint16> set_of_dorm_number; //宿舍号set

    DormListModel *model_dorm;  //宿舍model
    StudentListModel *model_student;    //住宿学生model

    //用户信息
    QMap<QString, QString> map_dorm_manager;
    QMap<QString, QString> map_data_manager;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_DATA_MANAGER_H
