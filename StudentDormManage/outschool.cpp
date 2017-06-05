#include "outschool.h"

//离校and晚归记录类实现
outschool::outschool()
{

}

outschool::outschool(const QString &na,const quint16 &Dorm, const QString &ID,const QString &Co,const QDateTime &time):
Name(na),DormNumber(Dorm),Contact(Co),IdNumber(ID),OutTime(time){

}

//获取姓名
const QString& outschool::GetName() const
{
    return Name;
}

//获取联系方式
const QString& outschool::GetContact() const
{
    return Contact;
}

//获取时间
const QDateTime& outschool::GetOutTime() const
{
    return OutTime;
}

//获取学号
const QString& outschool::GetIdNumber() const
{
    return IdNumber;
}

//获取宿舍号
const quint16& outschool::GetDormNumber() const
{
    return DormNumber;
}

//重载输入输出运算符
QDataStream & operator <<(QDataStream &out, const outschool &obj)
{
    out << obj.Name  << obj.DormNumber << obj.IdNumber << obj.Contact
         << obj.OutTime ;
    return out;
}

QDataStream & operator >>(QDataStream &in, outschool &obj)
{
    in >> obj.Name  >> obj.DormNumber >> obj.IdNumber >> obj.Contact
        >> obj.OutTime;
    return in;
}
