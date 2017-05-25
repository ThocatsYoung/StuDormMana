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
protected:
    QString Name;  //名字
    bool Sexuality;  //性别, 男true 女false
    QString Contact;    //联系方式
public:
    people();
    people(const QString &na, const bool sex, const QString &contact);

    /*属性设置函数*/
    void SetName(const QString &NewName);   //设置名字
    void SetSexuality(const bool RealSex); //设置性别
    void SetContact(const QString &NewContact); //设置联系方式

    /*属性值获取函数*/
    const QString& GetName(); //获取名字
    const bool& GetSexuality();  //获取性别
    const QString& GetContact();  //获取联系方式

};


//外来人员<-人
class outsider: public people
{
protected:
    bool HasGone;   //是否离开
    QDateTime ComeTime; //来访时间
    QDateTime GoTime;   //离开时间（构造函数未定义）
public:
    outsider();
    outsider(const QString &na, const bool sex, const QString &contact,
             const QDateTime &cometime = QDateTime::currentDateTime());
    void gone(const QDateTime gotime);   //离开时调用

    /*属性值获取函数*/
    const bool GetHasGone();
    const QDateTime& GetComeTime();
    const QDateTime& GetGoTime();

    /*属性设置函数*/
    void SetHasGone(const bool hasgone);
    void SetComeTime(const QDateTime &cometime);
    void SetGoTime(const QDateTime &gotime);

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const outsider &obj);
    friend QDataStream &operator >>(QDataStream &in, outsider &obj);
};


//住宿人员<-人
class resident:public people
{
protected:
    quint16 DormNumber; //宿舍号
    QDate ComeInDate;   //入住时间
    QString IdNumber;   //身份证号
public:
    resident();
    resident(const QString na, const bool sex, const QString &contact,
             const quint16 dN, const QDate comein, const QString id);

    /*属性值获取函数*/
    const QDate& GetComeInDate();
    const QString& GetIdNumber();
    const quint16& GetDormNumber();

    /*属性设置函数*/
    void SetDormNumber(const quint16 dorm);
    void SetComeInDate(const QDate &comeindate);
    void SetIdNumber(const QString &idnumber);

};


//学生<-住宿人员<-人
class student: public resident
{
protected:
    QString StudentId;  //学号
    quint16 XueYuan;  //学院编号，用类静态字符串Map下标访问
    quint16 BanJi;  //班级编号，用类静态字符串Map下标访问
    bool InSchool;  //是否在校
    QDate LastGoTime;   //最近一次离开时间
    QDate LastBackTime; //最近一次归校时间
public:
    student();
    student(const QString &na, const bool sex, const QString &contact,
            const quint16 dN, const QDate &comein, const QString &id,
            const QString &stuid,const quint16 &xueyuan, const quint16 &bj);

    /*属性值获取函数*/
    const QString& GetStudentId();
    const quint16& GetXueYuan();
    const quint16& GetBanJi();
    const bool& GetInSchool();
    const QDate& GetLastGoTime();
    const QDate& GetLastBackTime();

    /*属性值设置函数*/
    void SetStudentId(const QString &stuid);
    void SetXueYuan(const quint16 xueyuan);
    void SetBanji(const quint16 banji);
    void SetInSchool(const bool inschool);
    void SetLastGoTime(const QDate &lastgo);
    void SetLastBackTime(const QDate &lastback);

    // 离/归校
    void leaveSchool(const QDate& leaveTime);
    void backSchool(const QDate& backTime);

    //输入输出运算符重载;
    friend QDataStream &operator <<(QDataStream &out, const student &obj);
    friend QDataStream &operator >>(QDataStream &in, student &obj);
};

//教职工<-住宿人员<-人 （暂不使用）


#endif // PEOPLE_H



