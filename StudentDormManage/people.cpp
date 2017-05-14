#include <cstring>

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
people::people(const QString &na, bool sex, const QString &contact)
    :Name(na), Sexuality(sex), Contact(contact)
{}
QString& people::Contact() const
{
    return Contact;
}

QDataStream &people::operator <<(QDataStream &out, const people &peo)
{
    out << peo.Name << peo.Sexuality << peo.Contact;
    return out;
}

QDataStream &people::operator >>(QDataStream &in, people &peo)
{
    in >> peo.Name >> peo.Sexuality >> peo.Contact;
    return in;
}
QString& people::Name() const
{
    return Name;
}
bool& people::GetSexuality() const
{
    return Sexuality;
}

//outsider 外来人员类实现

outsider::outsider(const QString na,bool sex, const QString contact,
                   const QDateTime cometime):
    people(na, sex, contact),ComeTime(cometime), hasgone(false){}

void outsider::gone(const QDateTime gotime)
{
    GoTime = gotime;
    hasGone = true;
}

bool outsider::GethasGone() const
{
    return hasgone();
}

QDateTime& outsider::GetComeTime() const
{
    return ComeTime;
}

QDateTime& outsider::GetGoTime() const
{
    return GoTime;
}

QDataStream &outsider::operator <<(QDataStream &out, const outsider &outs)
{
    out << outs.hasGone << outs.ComeTime << outs.GoTime;
    return out;
}

QDataStream &outsider::operator >>(QDataStream &in, outsider &outs)
{
    in >> outs.hasGone << outs.ComeTime << outs.GoTime;
    return in;
}

//resident 住宿人员类实现
resident::resident(const QString na, bool sex, const QString &contact,
                   quint32 dN, QDate comein, QString id):
    people(na, sex, contact), DormNumber(dN),
    ComeInDate(comein), IdNumber(id){}

QDate &resident::GetComeInDate() const
{
    return ComeInDate;
}

QString &resident::GetIdNumber() const
{
    return IdNumber;
}

quint32 &resident::GetDormNumber() const
{
    return DormNumber;
}

QDataStream &resident::operator <<(QDataStream &out, const resident &res)
{
    out << res.DormNumber << res.ComeInDate << res.IdNumber;
    return out;
}

QDataStream &resident::operator >>(QDataStream &in, resident &res)
{
    in >> res.DormNumber >> res.ComeInDate >> res.IdNumber;
    return in;
}

//banji 班级类实现
banji::banji(quint8 g, QString m, quint8 bjh):
    Grade(g), Major(m), BanJiHao(bjh){}

quint8 &banji::GetGrade() const
{
    return Grade;
}

quint8 &banji::GetBanJiHao() const
{
    return BanJiHao;
}

QString &banji::GetMajor() const
{
    return Major;
}

QDataStream &banji::operator <<(QDataStream &out, const banji &ban)
{
    out << ban.Grade << ban.Major << ban.BanJiHao;
    return out;
}

QDataStream &banji::operator >>(QDataStream &in, banji &ban)
{
    in >> ban.Grade >> ban.Major >> ban.BanJiHao;
    return in;
}

//student 学生类实现

student::student(const QString na, bool sex, const QString &contact,
                 quint32 dN, QDate comein, QString id,
                 QString stuid, banji bj, QDate lbt):
    resident(na, sex, contact, dN, comein, id),
    StudentId(stuid), BanJi(banji), LastBackTime(lbt), InSchool(true){}

QString &student::GetStudentId() const
{
    return StudentId;
}

banji &student::GetBanJi() const
{
    return BanJi;
}

bool &student::GetInSchool() const
{
    return InSchool;
}

QDate &student::GetLastGoTime() const
{
    return LastGoTime;
}

QDate &student::GetLastBackTime() const
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

QDataStream &student::operator <<(QDataStream &out, const student &stu)
{
    out << stu.StudentId << stu.BanJi << stu.InSchool
        << stu.LastGoTime << stu.LastBackTime;
    return out;
}

QDataStream &student::operator >>(QDataStream &in, student &stu)
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

QString &teacher::GetInstitute() const
{
    return Institute;
}

QString &teacher::GetTitle() const
{
    return Title;
}

QDataStream &teacher::operator <<(QDataStream &out, const teacher &tea)
{
    out << tea.Institute << tea.Title;
    return out;
}

QDataStream &teacher::operator >>(QDataStream &in, teacher &tea)
{
    out << tea.Institute << tea.Title;
    return in;
}
