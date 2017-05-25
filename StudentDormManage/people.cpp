#include <QDateTime>
#include <QString>
#include <QDataStream>

#include "people.h"
//people类实现
void people::SetName(const QString &NewName)
{
    Name = NewName;
    return;
}
void people::SetContact(const QString &NewContact)
{
    Contact = NewContact;
    return;
}
void people::SetSexuality(const bool RealSex)
{
    Sexuality = RealSex;
    return;
}
people::people()
{

}

people::people(const QString &na, const bool sex, const QString &contact)
    :Name(na), Sexuality(sex), Contact(contact)
{}
const QString& people::GetContact()
{
    return Contact;
}

const QString& people::GetName()
{
    return Name;
}
const bool& people::GetSexuality()
{
    return Sexuality;
}

//outsider 外来人员类实现

outsider::outsider()
{

}

outsider::outsider(const QString &na, const bool sex, const QString &contact,
                   const QDateTime &cometime):
    people(na, sex, contact),ComeTime(cometime), HasGone(false){}

void outsider::gone(const QDateTime gotime)
{
    GoTime = gotime;
    HasGone = true;
}

const bool outsider::GetHasGone()
{
    return HasGone;
}

const QDateTime& outsider::GetComeTime()
{
    return ComeTime;
}

const QDateTime& outsider::GetGoTime()
{
    return GoTime;
}

void outsider::SetHasGone(const bool hasgone)
{
    HasGone = hasgone;
}

void outsider::SetComeTime(const QDateTime &cometime)
{
    ComeTime = cometime;
}

void outsider::SetGoTime(const QDateTime &gotime)
{
    GoTime = gotime;
}

QDataStream & operator <<(QDataStream &out, const outsider &obj)
{
    out << obj.Name << obj.Sexuality << obj.Contact
        << obj.HasGone << obj.ComeTime << obj.GoTime;
    return out;
}

QDataStream & operator >>(QDataStream &in, outsider &obj)
{
    in >> obj.Name >> obj.Sexuality >> obj.Contact
       >> obj.HasGone >> obj.ComeTime >> obj.GoTime;
    return in;
}

//resident 住宿人员类实现
resident::resident()
{

}

resident::resident(const QString na, const bool sex, const QString &contact,
                   const quint16 dN, const QDate comein, const QString id):
    people(na, sex, contact), DormNumber(dN),
    ComeInDate(comein), IdNumber(id){}

const QDate &resident::GetComeInDate()
{
    return ComeInDate;
}

const QString &resident::GetIdNumber()
{
    return IdNumber;
}

const quint16 &resident::GetDormNumber()
{
    return DormNumber;
}

void resident::SetDormNumber(const quint16 dorm)
{
    DormNumber = dorm;
}

void resident::SetComeInDate(const QDate &comeindate)
{
    ComeInDate = comeindate;
}

void resident::SetIdNumber(const QString &idnumber)
{
    IdNumber = idnumber;
}



//student 学生类实现

student::student()
{

}

student::student(const QString &na, const bool sex, const QString &contact,
                 const quint16 dN, const QDate &comein, const QString &id,
                 const QString &stuid, const quint16 &xueyuan, const quint16 &bj):
    resident(na, sex, contact, dN, comein, id),
    StudentId(stuid), XueYuan(xueyuan),BanJi(bj),
    LastGoTime(comein), LastBackTime(comein), InSchool(true){}

const QString &student::GetStudentId()
{
    return StudentId;
}

const quint16 &student::GetXueYuan()
{
    return XueYuan;
}

const quint16 &student::GetBanJi()
{
    return BanJi;
}

const bool &student::GetInSchool()
{
    return InSchool;
}

const QDate &student::GetLastGoTime()
{
    return LastGoTime;
}

const QDate &student::GetLastBackTime()
{
    return LastBackTime;
}

void student::SetStudentId(const QString &stuid)
{
    StudentId = stuid;
}

void student::SetXueYuan(const quint16 xueyuan)
{
    XueYuan = xueyuan;
}

void student::SetBanji(const quint16 banji)
{
    BanJi = banji;
}

void student::SetInSchool(const bool inschool)
{
    InSchool = inschool;
}

void student::SetLastGoTime(const QDate &lastgo)
{
    LastGoTime = lastgo;
}

void student::SetLastBackTime(const QDate &lastback)
{
    LastBackTime = lastback;
}

void student::leaveSchool(const QDate& leaveTime)
{
    LastGoTime = leaveTime;
    InSchool = false;
}

void student::backSchool(const QDate& backTime)
{
    LastBackTime = backTime;
    InSchool = true;
}

QDataStream & operator <<(QDataStream &out, const student &obj)
{
    out << obj.Name << obj.Sexuality << obj.Contact
        << obj.DormNumber << obj.ComeInDate << obj.IdNumber
        << obj.StudentId << obj.XueYuan << obj.BanJi
        << obj.InSchool << obj.LastGoTime << obj.LastBackTime;
    return out;
}

QDataStream & operator >>(QDataStream &in, student &obj)
{
    in >> obj.Name >> obj.Sexuality >> obj.Contact
       >> obj.DormNumber >> obj.ComeInDate >> obj.IdNumber
       >> obj.StudentId >> obj.XueYuan >> obj.BanJi
       >> obj.InSchool >> obj.LastGoTime >> obj.LastBackTime;
    return in;
}

//teacher 教师类实现（暂不使用）

