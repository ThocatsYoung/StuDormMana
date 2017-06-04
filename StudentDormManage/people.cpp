#include <QDateTime>
#include <QString>
#include <QDataStream>

#include "people.h"

const QStringList people::text_of_sex = {
    "女","男"
};

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
const QString& people::GetContact() const
{
    return Contact;
}

const QString& people::GetName() const
{
    return Name;
}
const bool& people::GetSexuality() const
{
    return Sexuality;
}


//resident 住宿人员类实现
resident::resident()
{

}

resident::resident(const QString na, const bool sex, const QString &contact,
                   const quint16 dN, const QString id):
    people(na, sex, contact), DormNumber(dN),
    IdNumber(id){}

const QString &resident::GetIdNumber() const
{
    return IdNumber;
}

const quint16 &resident::GetDormNumber() const
{
    return DormNumber;
}

void resident::SetDormNumber(const quint16 dorm)
{
    DormNumber = dorm;
}

void resident::SetIdNumber(const QString &idnumber)
{
    IdNumber = idnumber;
}



//student 学生类实现

QStringList student::list_of_XueYuan;

QList<QStringList> student::lists_of_BanJi;


student::Init_of_Xueyuan_and_BanJi()
{

    list_of_XueYuan.append("计算机科学与工程学院");
    list_of_XueYuan.append("数学学院");
    list_of_XueYuan.append("软件学院");

    QStringList computer = {"15计科", "15网工", "16计科1", "16网工"};
    QStringList math = {"15应用数学", "15计算数学", "16应用数学", "16计算数学"};
    QStringList software = {"15软件工程", "16软件工程"};

    lists_of_BanJi.append(computer);
    lists_of_BanJi.append(math);
    lists_of_BanJi.append(software);

}

student::student()
{

}

student::student(const QString &na, const bool sex, const QString &contact,
                 const quint16 dN, const QString &id,
                 const QString &stuid, const quint16 &xueyuan, const quint16 &bj):
    resident(na, sex, contact, dN, id),
    StudentId(stuid), XueYuan(xueyuan),BanJi(bj)
{

}

const QString &student::GetStudentId() const
{
    return StudentId;
}

const quint16 &student::GetXueYuan() const
{
    return XueYuan;
}

const quint16 &student::GetBanJi() const
{
    return BanJi;
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


QString student::toString()
{
    QString xueyuan_text = list_of_XueYuan.value(this->GetXueYuan(),
                                                 list_of_XueYuan.last());
    QString student_info("姓名："+this->GetName()+'\n'+
                         "学号："+this->GetStudentId()+'\n'+
                         "宿舍号："+QString("%1").arg(this->GetDormNumber())+'\n'+
                         "学院："+xueyuan_text+'\n'+
                         "联系方式："+this->GetContact()+'\n');
    return student_info;
}

QString student::toString_detail()
{
    //未事先检查下标是否越界
    QString xueyuan_text = list_of_XueYuan.at(this->GetXueYuan());
    QString banji_text = lists_of_BanJi.at(this->GetXueYuan()).at(this->GetBanJi());

    QString student_info("姓名："+this->GetName()+'\n'+
                         "学号："+this->GetStudentId()+'\n'+
                         "宿舍号："+QString("%1").arg(this->GetDormNumber())+'\n'+
                         "学院："+xueyuan_text+'\n'+
                         "班级："+banji_text+'\n'+
                         "身份证号："+QString("%1").arg(this->GetIdNumber())+'\n'+
                         "联系方式："+this->GetContact()+'\n');

    return student_info;
}



bool operator <(student &a, student &b)
{
    return (a.GetStudentId() < b.GetStudentId());
}

QDataStream & operator <<(QDataStream &out, const student &obj)
{
    out << obj.Name << obj.Sexuality << obj.Contact
        << obj.DormNumber << obj.IdNumber
        << obj.StudentId << obj.XueYuan << obj.BanJi;
    return out;
}

QDataStream & operator >>(QDataStream &in, student &obj)
{
    in >> obj.Name >> obj.Sexuality >> obj.Contact
       >> obj.DormNumber >> obj.IdNumber
       >> obj.StudentId >> obj.XueYuan >> obj.BanJi;
    return in;
}


