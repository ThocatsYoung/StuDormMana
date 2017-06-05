#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

//测试 github 用注释

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QDataStream>
#include <QDebug>
#include <QMessageBox>

#define DEBUG_TEST 0    //控制测试代码是否编译

//文件路径常量定义
const QString path_of_data_manager("data_manager.dat");   //住宿信息管理人员信息
const QString path_of_dorm_manager("dorm_manager.dat");   //宿舍管理员信息

const QString path_of_data_dorm("information_of_dorms.dat");   //宿舍信息

const QString path_of_rulebreak_record("rulebreak_record.dat"); //宿舍违纪记录
const QString path_of_rulebreak_record_past("rulebreak_record_past.dat");   //宿舍违纪历史记录

const QString path_of_wailairen_record("wailairen_record.dat");   //外访信息
const QString path_of_wailairen_record_past("wailairen_record_past.dat");    //历史外访信息
const QString path_of_outschool_record("outschool_record.dat");   //离校信息
const QString path_of_outschool_record_past("outschool_record_past.dat");    //历史离校信息
const QString path_of_wangui_record("wangui_record.dat");   //晚归信息
const QString path_of_wangui_record_past("wangui_record_past.dat");    //历史晚归信息


//在文件不存在时建立以path命名的空文件
void build_file_if_have_no(QString path);

//在文件夹不存在时创建
void create_dir_if_no_exist(QString path_dir);

//在文件夹存在时删除
void delete_dir_if_exist(QString path_dir);

//以'/'连接字符串作为文件路径
QString add_user_and_path(QString user, QString path);

//消息框警告信息
void warning_message_box(QString warn);
//消息框提示消息
void information_message_box(QString info);
//消息框询问, 确定返回true 取消返回false
bool ask_yes_or_no(QString s);

//文件内容读入容器
template <typename T>
void read_file_to_container(QString path, T &container)
{
    build_file_if_have_no(path);

    if (path.isEmpty())
        warning_message_box("文件路径为空！");
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << (path+"\ncan't open this file") << endl;
        warning_message_box(path+"\n无法读取文件");
        return;
    }
    QDataStream f(&file);
    f >> container;
    file.close();
}

//容器内容写入文件
template <typename T>
void write_container_to_file(T &container, QString path)
{
    if (path.isEmpty()){
        warning_message_box("文件路径为空！");
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << (path+"\ncan't open this file") << endl;
        warning_message_box(path+"\n无法写入文件");
        return;
    }
    QDataStream f(&file);
    f << container;
    file.close();
}



#endif // READ_FROM_FILE_H
