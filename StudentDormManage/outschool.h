#ifndef OUTSCHOOL_H
#define OUTSCHOOL_H

#include "read_from_file.h"

#include <QString>
#include <QDateTime>


//离校记录类and晚归登记类
class outschool
{
protected:
    QString Name;     //学生姓名
    QString IdNumber;//学号
    QString Contact;//联系方式
    QDateTime OutTime;//离开时间and晚归时间
    quint16 DormNumber;//宿舍号


public:
    outschool();
    outschool(const QString &na,const quint16 &Dorm,const QString &ID,const QString &Co,const QDateTime &time);//构造函数
    const QString& GetName() const; //获取名字
    const QString& GetContact() const;  //获取联系方式
    const QDateTime& GetOutTime() const;//获取时间
    const QString& GetIdNumber() const;//获取学号
    const quint16& GetDormNumber() const;//获取宿舍号
    friend QDataStream &operator <<(QDataStream &out, const outschool &obj);//重载输出运算符
    friend QDataStream &operator >>(QDataStream &in, outschool &obj);//重载输入运算符
};

#endif // OUTSCHOOL_H
