#ifndef PEOPLE_H
#define PEOPLE_H

#include <QDateTime>
#include <QString>
#include <QDataStream>

//在构造函数中没有设置数据合法性检查，该功能设置在 添删改 的功能模块中
//由于大量使用了Qt基类，无需使用动态内存分配，故构造函数中无参数构造内容为空，同时复制构造函数均由编译器自动生成

//重载运算符<<、>>实现待争议
//部分属性设置函数将在以后编写
//QString 不改了
//放弃外租人员类，教师类

//基类_人
class people
{
    QString Name;  //名字
    bool Sexuality;  //性别, 男true 女false
    QString Contact;    //联系方式
public:
    people();
    people(const QString &na, bool sex, const QString &contact);

    /*属性设置函数*/
    void SetName(const QString &NewName);   //设置名字
    void SetSexuality(bool RealSex); //设置性别
    void SetContact(const QString &NewContact); //设置联系方式

    /*属性值获取函数*/
    const QString& GetName(); //获取名字
    const bool& GetSexuality();  //获取性别
    const QString& GetContact();  //获取联系方式

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const people &peo);
    friend QDataStream &operator >>(QDataStream &in, people &peo);
};


//外来人员<-人
class outsider: public people
{
    bool HasGone;   //是否离开
    QDateTime ComeTime; //来访时间
    QDateTime GoTime;   //离开时间（构造函数未定义）
public:
    outsider();
    outsider(const QString &na,bool sex, const QString &contact,
             const QDateTime &cometime);
    void gone(const QDateTime gotime);   //离开时调用

    /*属性值获取函数*/
    const bool GetHasGone();
    const QDateTime& GetComeTime();
    const QDateTime& GetGoTime();

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const outsider &outs);
    friend QDataStream &operator >>(QDataStream &in, outsider &outs);
};


//住宿人员<-人
class resident:public people
{
    quint16 DormNumber; //宿舍号
    QDate ComeInDate;   //入住时间
    QString IdNumber;   //身份证号
public:
    resident();
    resident(const QString na, bool sex, const QString &contact,
             quint16 dN, QDate comein, QString id);

    /*属性值获取函数*/
    const QDate& GetComeInDate();
    const QString& GetIdNumber();
    const quint16& GetDormNumber();

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const resident &res);
    friend QDataStream &operator >>(QDataStream &in, resident &res);
};


//学生<-住宿人员<-人
class student: public resident
{
    QString StudentId;  //学号
    quint16 XueYuan;  //学院编号，用类静态字符串Map下标访问
    quint16 BanJi;  //班级编号，用类静态字符串Map下标访问
    bool InSchool;  //是否在校
    QDate LastGoTime;   //最近一次离开时间
    QDate LastBackTime; //最近一次归校时间
public:
    student();
    student(const QString &na, bool sex, const QString &contact,
            quint16 dN, QDate &comein, QString &id,
            QString &stuid,quint16 &xueyuan, quint16 &bj);

    /*属性值获取函数*/
    const QString& GetStudentId();
    const quint16& GetXueYuan();
    const quint16& GetBanJi();
    const bool& GetInSchool();
    const QDate& GetLastGoTime();
    const QDate& GetLastBackTime();

    // 离/归校
    void leaveSchool(QDate& leaveTime);
    void backSchool(QDate& backTime);

    //输入输出运算符重载;
    friend QDataStream &operator <<(QDataStream &out, const student &stu);
    friend QDataStream &operator >>(QDataStream &in, student &stu);
};

//教职工<-住宿人员<-人 （暂不使用）


#endif // PEOPLE_H




