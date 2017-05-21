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
void people::SetSexuality(bool RealSex)
{
    Sexuality = RealSex;
    return;
}
people::people()
{

}

people::people(const QString &na, bool sex, const QString &contact)
    :Name(na), Sexuality(sex), Contact(contact)
{}
const QString& people::GetContact()
{
    return Contact;
}

QDataStream& operator <<(QDataStream &out, const people &peo)
{
    out << peo.Name << peo.Sexuality << peo.Contact;
    return out;
}

QDataStream& operator >>(QDataStream &in, people &peo)
{
    in >> peo.Name >> peo.Sexuality >> peo.Contact;
    return in;
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

outsider::outsider(const QString &na,bool sex, const QString &contact,
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

QDataStream & operator <<(QDataStream &out, const outsider &outs)
{
    out << outs.HasGone << outs.ComeTime << outs.GoTime;
    return out;
}

QDataStream & operator >>(QDataStream &in, outsider &outs)
{
    in >> outs.HasGone >> outs.ComeTime >> outs.GoTime;
    return in;
}

//resident 住宿人员类实现
resident::resident()
{

}

resident::resident(const QString na, bool sex, const QString &contact,
                   quint32 dN, QDate comein, QString id):
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

const quint32 &resident::GetDormNumber()
{
    return DormNumber;
}

QDataStream & operator <<(QDataStream &out, const resident &res)
{
    out << res.DormNumber << res.ComeInDate << res.IdNumber;
    return out;
}

QDataStream & operator >>(QDataStream &in, resident &res)
{
    in >> res.DormNumber >> res.ComeInDate >> res.IdNumber;
    return in;
}

//banji 班级类实现
banji::banji(quint8 g, QString m, quint8 bjh):
    Grade(g), Major(m), BanJiHao(bjh){}

banji::banji()
{

}

const quint8 &banji::GetGrade()
{
    return Grade;
}

const quint8 &banji::GetBanJiHao()
{
    return BanJiHao;
}

const QString &banji::GetMajor()
{
    return Major;
}

QDataStream & operator <<(QDataStream &out, const banji &ban)
{
    out << ban.Grade << ban.Major << ban.BanJiHao;
    return out;
}

QDataStream & operator >>(QDataStream &in, banji &ban)
{
    in >> ban.Grade >> ban.Major >> ban.BanJiHao;
    return in;
}

//student 学生类实现

student::student()
{

}

student::student(const QString &na, bool sex, const QString &contact,
                 quint32 dN, QDate &comein, QString &id,
                 QString &stuid, banji &bj):
    resident(na, sex, contact, dN, comein, id),StudentId(stuid),
    BanJi(bj), LastGoTime(comein), LastBackTime(comein), InSchool(true){}

const QString &student::GetStudentId()
{
    return StudentId;
}

const banji &student::GetBanJi()
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

void student::leaveSchool(QDate& leaveTime)
{
    LastGoTime = leaveTime;
    InSchool = false;
}

void student::backSchool(QDate& backTime)
{
    LastBackTime = backTime;
    InSchool = true;
}

QDataStream & operator <<(QDataStream &out, const student &stu)
{
    out << stu.StudentId << stu.BanJi << stu.InSchool
        << stu.LastGoTime << stu.LastBackTime;
    return out;
}

QDataStream & operator >>(QDataStream &in, student &stu)
{
    in >> stu.StudentId >> stu.BanJi >> stu.InSchool
       >> stu.LastGoTime >> stu.LastBackTime;
    return in;
}

//teacher 教师类实现
teacher::teacher(const QString na, bool sex, const QString &contact,
                 quint32 dN, QDate comein, QString id,
                 QString institute, QString title):
    resident(na, sex, contact, dN, comein, id),
    Institute(institute), Title(title){}

const QString &teacher::GetInstitute()
{
    return Institute;
}

const QString &teacher::GetTitle()
{
    return Title;
}

QDataStream & operator <<(QDataStream &out, const teacher &tea)
{
    out << tea.Institute << tea.Title;
    return out;
}

QDataStream & operator >>(QDataStream &in, teacher &tea)
{
    in >> tea.Institute >> tea.Title;
    return in;
}
