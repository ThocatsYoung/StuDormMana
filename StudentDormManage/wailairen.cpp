#include "wailairen.h"

//outsider 外来人员类实现

QStringList outsider::sex_things =
{"男", "女"};

outsider::outsider()
{

}

outsider:: outsider(const QString &na, const quint16 msex,const QString idnumber, const QString &contact,
                    const QDateTime &cometime):
   Name(na),m_sex(msex),Contact(contact),IdNumber(idnumber),ComeTime(cometime)
{

}

//设置姓名
void outsider::SetName(const QString &NewName)
{
    Name = NewName;
    return;
}
//--------------------属性设置-------------------
//设置联系方式
void outsider::SetContact(const QString &NewContact)
{
    Contact = NewContact;
    return;
}

//设置来访时间
void outsider::SetComeTime(const QDateTime &cometime)
{
    ComeTime = cometime;
}

//设置ID
void outsider::SetIdNumber(const QString &idnumber)
{
    IdNumber = idnumber;
}
//--------------属性获取--------------------
//获取联系方式
const QString& outsider::GetContact() const
{
    return Contact;
}

//获取姓名
const QString& outsider::GetName() const
{
    return Name;
}

//获取性别
const quint16& outsider::get_sex() const
{
    return m_sex;
}

//获取来访时间
const QDateTime& outsider::GetComeTime() const
{
    return ComeTime;
}

//获取ID
const QString& outsider::GetIdNumber() const
{
    return IdNumber;
}

//重载输入输出运算符
QDataStream & operator <<(QDataStream &out, const outsider &obj)
{
    out << obj.Name << obj.m_sex << obj.IdNumber << obj.Contact
         << obj.ComeTime ;
    return out;
}

QDataStream & operator >>(QDataStream &in, outsider &obj)
{
    in >> obj.Name >> obj.m_sex >> obj.IdNumber >> obj.Contact
        >> obj.ComeTime;
    return in;
}
