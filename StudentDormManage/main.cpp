#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QMap>

#include "read_from_file.h"
#include "people.h"
#include "room.h"
#include "dormlistmodel.h"
#include "formforrulebreakrecord.h"
#include "dialog_login.h"
#include "mainwindow_data_manager.h"

#define DEBUG_TEST 0    //控制测试代码是否编译



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //初始化文件路径
    QString path_of_data_manager("data_manager.dat");   //住宿信息管理人员信息
    QString path_of_dorm_manager("dorm_manager.dat");   //宿舍管理员信息

    QString test_file(":/dats/dorm_information.dat");   //宿舍信息
    QString path_of_rulebreak_record("rulebreak_record.dat");   //违纪信息
    QString path_of_rulebreak_record_past("rulebreak_record_past.dat");    //历史违纪信息

    //测试用创建文件
#if DEBUG_TEST
    QMap<QString,QString> fortest;
    write_container_to_file(fortest, path_of_data_manager);
    write_container_to_file(fortest, path_of_dorm_manager);
#endif

    //登录
    Dialog_Login login (path_of_data_manager, path_of_dorm_manager);

    if(login.exec() != QDialog::Accepted)
    {
        return 0;
    }

    //读取文件
    QList<dorm> dorm_list;
    read_file_to_container(test_file, dorm_list);

    //将list中的每个student地址(value)及其studentid(key)读入map (java风格迭代器)
    QMap<QString, student*> map_stuid;
    for(QMutableListIterator<dorm> i(dorm_list); i.hasNext();)
    {
        QMutableListIterator<student> j(i.next().StuDorm);
        while(j.hasNext())
        {
            student *stu = &j.next();
            if(map_stuid.contains(stu->GetStudentId()))
                continue;
            map_stuid.insert(stu->GetStudentId(),stu);
        }
    }

#if DEBUG_TEST
    foreach (student* stu, map_stuid)
    {
        qDebug() << stu->GetName();
        qDebug() << stu->GetStudentId();
    }
#endif


    //创建宿舍管理主窗口
    if(Dialog_Login::login_type == 0)   //宿管登录
    {
        MainWindow w;
        w.setWindowTitle("学生宿舍管理系统v0.3");

        FormForRuleBreakRecord Form_rulebreak(path_of_rulebreak_record,path_of_rulebreak_record_past);
        w.add_widget_to_tabwidget(&Form_rulebreak);

        //设置主窗口数据指针
        w.set_m_list_of_dorm(&dorm_list);
        w.set_m_map_find_by_student_id(&map_stuid);


        //创建、设置model/view
        DormListModel *m = new DormListModel(&dorm_list, &w);
        w.set_listview_dorm_model(m);
        StudentListModel *slm = new StudentListModel(&dorm_list, &(dorm_list[0].StuDorm),&w);
        w.set_tableview_students_model(slm);

        //连接
        w.lianjie_students_model_and_listview_dorm(slm);

        //显示窗口
        w.show();
        return a.exec();
    }else{
        //创建住宿数据管理员界面
        if(Dialog_Login::login_type == 1)
        {
            MainWindow_data_manager w;
            w.show();
            return a.exec();
        }
        else
            return 0;
    }
    return 0;
}
