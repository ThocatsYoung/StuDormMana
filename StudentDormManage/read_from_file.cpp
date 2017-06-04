#include "read_from_file.h"


void build_file_if_have_no(QString path)
{
    QFileInfo file(path);
    if(!file.isFile())  //不存在时新建文件
    {
        QFile f(path);
        f.open(QIODevice::WriteOnly);
        f.close();
        return;
    }else{
        return;
    }
}



void warning_message_box(QString warn)
{
    QMessageBox::warning(0, QObject::tr("警告！"), warn);
    return;
}

QString add_user_and_path(QString user, QString path)
{
    return QString("%1/%2").arg(user,path);
}

void create_dir_if_no_exist(QString path_dir)
{
    if (path_dir.isEmpty())
    {
        qDebug() << QString("path_dir is empty");
        return;
    }
    QFileInfo dir(path_dir);
    if (dir.isDir())
    {
        qDebug() << (path_dir+"\n this dir exists and no need to creat");
        return;
    }else{
        QDir new_dir;
        new_dir.mkdir(path_dir);
    }
}

void delete_dir_if_exist(QString path_dir)
{
    if (path_dir.isEmpty())
    {
        qDebug() << QString("path_dir is empty");
        return;
    }
    QFileInfo d(path_dir);
    if (d.isDir()){
        QDir dir(path_dir);
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        QFileInfoList fileList = dir.entryInfoList();
        foreach (QFileInfo fi, fileList)
        {
            if (fi.isFile())
                fi.dir().remove(fi.fileName());
            else
                delete_dir_if_exist(fi.absoluteFilePath());
        }
        dir.rmpath(dir.absolutePath());
        qDebug() << "the dir is deleted";
        return;
    }else{
        qDebug() << (path_dir+"\n this dir doesn't exist and can't be deleted");
        return;
    }
}

void information_message_box(QString info)
{
    QMessageBox::information(0,QObject::tr("信息"),info);
    return;
}
