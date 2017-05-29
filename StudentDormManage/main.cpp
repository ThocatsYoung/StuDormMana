#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QMap>

#include "people.h"
#include "room.h"
#include "dormlistmodel.h"
#include "formforrulebreakrecord.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //从文件中读取宿舍信息
    QString test_file(":/dats/dorm_information.dat");   //宿舍信息
    QString path_of_rulebreak_record("rulebreak_record.dat");   //违纪信息
    QString path_of_rulebreak_record_past("rulebreak_record_past.dat");    //历史违纪信息

    //读取宿舍信息文件
    QFile file_dorm_info(test_file);
    if(!file_dorm_info.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open file for writing";
        QMessageBox::warning(0, QObject::tr("错误！"), QObject::tr("无法读取宿舍人员信息文件"));
        return 0;
    }
    QDataStream f(&file_dorm_info);
    QList<dorm> dorm_list;
    f >> dorm_list;
    file_dorm_info.close();



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
    foreach (student* stu, map_stuid)
    {
        qDebug() << stu->GetName();
        qDebug() << stu->GetStudentId();
    }


    //创建主窗口
    MainWindow w;

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
}
