#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QValidator>
#include <QMap>
#include <QPair>
#include <QSet>

#include "dormlistmodel.h"
#include "studentlistmodel.h"

#include "formforrulebreakrecord.h"
#include "formforoutschool.h"
#include "formforoutsider.h"
#include "formforwangui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString user,
                        QWidget *parent = 0);
    ~MainWindow();

    void add_widget_to_tabwidget(QWidget* w, QString title);

//初始化数据结构
    void init_user_data();
    void init_list_of_dorm();
    void init_set_of_dorm_number();
    void init_map_of_student_id();


signals:
    void send_message_for_dorm_find(QString str);   //发送宿舍查找信息
    void send_point_of_student_list_to_model(QList<student> *p);    //发送学生list指针


private slots:

    void on_SwitchPushButton_clicked(); //切换界面

    void on_pushButton_to_dorm_clicked();   //跳转宿舍按钮槽函数

    void on_pushButton_find_by_stuid_clicked(); //以学号查找学生

    void change_dorm_information(); //改变宿舍信息（主要为listView显示改变）

public slots:
    void find_dorm_in_listview_dorm(QString dorm_number);   //以宿舍号查找宿舍并跳转

private:
    Ui::MainWindow *ui;

    //用户名及密码
    QString user_name;

    //宿舍楼数据
    QList<dorm> m_list_of_dorm; //底层宿舍信息链表
    QMap<QString, student*> m_map_find_by_student_id;   //学号-学生 map
    QSet<quint16> set_of_dorm_number;   //宿舍号set

    //model
    DormListModel *model_dorm;  //宿舍model
    StudentListModel *model_student;    //住宿学生model

    //宿舍管理员帐号map
    QMap <QString,QString> map_dorm_manager;


    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
