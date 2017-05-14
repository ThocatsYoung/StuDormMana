#ifndef PEOPLE_H
#define PEOPLE_H
#include <QDateTime>
#include <QString>

//在构造函数中没有设置数据合法性检查，该功能设置在 添删改 的功能模块中
//由于大量使用了Qt基类，无需使用动态内存分配，故构造函数均为默认构造函数

//重载运算符<<,>>实现待争议
//部分属性设置函数将在以后编写
//QString 不改了

//基类_人
class people
{
    QString Name;  //名字
    bool Sexuality;  //性别, 男true 女false
    QString Contact;    //联系方式
public:
    people(const QString na, bool sex, const QString contact);

    /*属性设置函数*/
    void SetName(const QString NewName);   //设置名字
    void SetSexuality(bool RealSex); //设置性别
    void SetContact(const QString NewContact[]); //设置联系方式

    /*属性值获取函数*/
    QString& GetName() const; //获取名字
    bool& GetSexuality() const;  //获取性别
    QString& GetContact() const;  //获取联系方式

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const people &peo);
    friend QDataStream &operator >>(QDataStream &in, people &peo);
};


//外来人员<-人
class outsider: public people
{
    bool hasGone;   //是否离开
    QDateTime ComeTime; //来访时间
    QDateTime GoTime;   //离开时间（构造函数未定义）
public:
    outsider(const QString na,bool sex, const QString contact,
             const QDateTime cometime);
    void gone(const QDateTime gotime);   //离开时调用

    /*属性值获取函数*/
    bool GethasGone() const;
    QDateTime& GetComeTime() const;
    QDateTime& GetGoTime() const;

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const outsider &outs);
    friend QDataStream &operator >>(QDataStream &in, outsider &outs);
};


//住宿人员<-人
class resident:public people
{
    quint32 DormNumber; //宿舍号
    QDate ComeInDate;   //入住时间
    QString IdNumber;   //身份证号
public:
    resident(const QString na, bool sex, const QString &contact,
             quint32 dN, QDate comein, QString id);

    /*属性值获取函数*/
    QDate& GetComeInDate() const;
    QString& GetIdNumber() const;
    quint32& GetDormNumber() const;

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const resident &res);
    friend QDataStream &operator >>(QDataStream &in, resident &res);
};

//班级(学生类子类)
//后续实现:打算用另外文件存储 班级的静态多维数组 。
class banji //由于与class关键字冲突，使用拼音命名
{
public:
    quint8 Grade;   //年级
    QString Major;  //专业
    quint8 BanJiHao;    //班级号
    banji(quint8 g, QString m, quint8 bjh);

    /*属性值获取函数*/
    quint8& GetGrade() const;
    quint8& GetBanJiHao() const;
    QString& GetMajor() const;

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const banji &ban);
    friend QDataStream &operator >>(QDataStream &in, banji &ban);
};

//学生<-住宿人员<-人
class student: public resident
{
    QString StudentId;  //学号
    banji BanJi;    //班级
    bool InSchool;  //是否在校
    QDate LastGoTime;   //最近一次离开时间（构造函数中未定义）
    QDate LastBackTime; //最近一次归校时间
public:
    student(const QString na, bool sex, const QString &contact,
            quint32 dN, QDate comein, QString id,
            QString stuid,banji bj, QDate lbt);

    /*属性值获取函数*/
    QString& GetStudentId() const;
    banji& GetBanJi() const;
    bool& GetInSchool() const;
    QDate& GetLastGoTime() const;
    QDate& GetLastBackTime() const;

    // 离/归校
    void leaveSchool(QDate& leaveTime);
    void backSchool(QDate& backTime);

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const student &stu);
    friend QDataStream &operator >>(QDataStream &in, student &stu);
};

//教职工<-住宿人员<-人 （存疑）
class teacher:public resident
{
    QString Institute;  //学院，可能会改成枚举变量或用类静态数组
    QString Title;  //职务,可能会改成枚举变量或用类静态数组
public:
    teacher(const QString na, bool sex, const QString &contact,
            quint32 dN, QDate comein, QString id,
            QString institute, QString title);

    /*属性值获取函数*/
    QString& GetInstitute() const;
    QString& GetTitle() const;

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const teacher &tea);
    friend QDataStream &operator >>(QDataStream &in, teacher &tea);
};

//外租人员<-居住者<-人 (未想好，以后再说）
class renter:public resident
{

};

#endif // PEOPLE_H




