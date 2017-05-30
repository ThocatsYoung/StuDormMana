#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QMessageBox>

//文件内容读入容器
template <typename T>
void read_file_to_container(QString path, T &container)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << (path+"\ncan't open this file") << endl;
        QMessageBox::warning(0, QObject::tr("错误！"), QObject::tr("\n无法读取文件"));
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
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << (path+"\ncan't open this file") << endl;
        QMessageBox::warning(0, QObject::tr("错误！"), QObject::tr("\n无法写入文件"));
        return;
    }
    QDataStream f(&file);
    f << container;
    file.close();
}

#endif // READ_FROM_FILE_H
