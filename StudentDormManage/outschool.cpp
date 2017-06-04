#include "outschool.h"

outschool::outschool()
{

}

outschool::outschool(const QString &na,const quint16 &Dorm, const QString &ID,const QString &Co,const QDateTime &time):
Name(na),DormNumber(Dorm),Contact(Co),IdNumber(ID),OutTime(time){

}

const QString& outschool::GetName() const
{
    return Name;
}

const QString& outschool::GetContact() const
{
    return Contact;
}

const QDateTime& outschool::GetOutTime() const
{
    return OutTime;
}

const QString& outschool::GetIdNumber() const
{
    return IdNumber;
}

const quint16& outschool::GetDormNumber() const
{
    return DormNumber;
}

QDataStream & operator <<(QDataStream &out, const outschool &obj)
{
    out << obj.Name  << obj.DormNumber << obj.IdNumber << obj.Contact
         << obj.OutTime ;
    return out;
}//_____________________________________________________________________

QDataStream & operator >>(QDataStream &in, outschool &obj)
{
    in >> obj.Name  >> obj.DormNumber >> obj.IdNumber >> obj.Contact
        >> obj.OutTime;
    return in;
}
