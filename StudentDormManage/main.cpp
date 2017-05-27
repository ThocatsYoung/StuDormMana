#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QMap>

#include "people.h"
#include "room.h"
#include "dormlistmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //从文件中读取宿舍信息
    QString test_file(":/dats/dorm_information.dat");
    QFile file_dorm_info(test_file);
    if(!file_dorm_info.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open file for writing";
        return 0;
    }
    QDataStream f(&file_dorm_info);
    QList<dorm> dorm_list;
    f >> dorm_list;
    file_dorm_info.close();
    //qDebug() << dorm_list.size(); 测试用代码

    //将list中的每个student地址(value)及其studentid(key)读入map
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
