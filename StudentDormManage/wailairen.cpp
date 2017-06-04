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

void outsider::SetName(const QString &NewName)
{
    Name = NewName;
    return;
}
void outsider::SetContact(const QString &NewContact)
{
    Contact = NewContact;
    return;
}
const QString& outsider::GetContact() const
{
    return Contact;
}

const QString& outsider::GetName() const
{
    return Name;
}
const quint16& outsider::get_sex() const
{
    return m_sex;
}
const QDateTime& outsider::GetComeTime() const
{
    return ComeTime;
}

void outsider::SetComeTime(const QDateTime &cometime)
{
    ComeTime = cometime;
}

void outsider::SetIdNumber(const QString &idnumber)
{
    IdNumber = idnumber;
}

const QString& outsider::GetIdNumber() const
{
    return IdNumber;
}//-------------------------------------------------------------------------------------
QDataStream & operator <<(QDataStream &out, const outsider &obj)
{
    out << obj.Name << obj.m_sex << obj.IdNumber << obj.Contact
         << obj.ComeTime ;
    return out;
}//_____________________________________________________________________

QDataStream & operator >>(QDataStream &in, outsider &obj)
{
    in >> obj.Name >> obj.m_sex >> obj.IdNumber >> obj.Contact
        >> obj.ComeTime;
    return in;
}
