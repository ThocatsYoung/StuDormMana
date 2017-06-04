#ifndef PEOPLE_H
#define PEOPLE_H

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QDataStream>


//resident 及 student 类 需要做较大改动

//由于大量使用了Qt基类，无需使用动态内存分配，故构造函数中无参数构造内容为空，同时复制构造函数均由编译器自动生成

//重载运算符<<、>>实现待争议
//部分属性设置函数将在以后编写
//QString 不改了
//放弃 外租人员类，教师类
//舍弃 外来人员类, 改用单独的纪录类实现外访登记功能

//基类_人
class people
{
protected:
    QString Name;  //名字
    bool Sexuality;  //性别, 男true 女false
    QString Contact;    //联系方式
public:
    const static QStringList text_of_sex;

    people();
    people(const QString &na, const bool sex, const QString &contact);

    /*属性设置函数*/
    void SetName(const QString &NewName);   //设置名字
    void SetSexuality(const bool RealSex); //设置性别
    void SetContact(const QString &NewContact); //设置联系方式

    /*属性值获取函数*/
    const QString& GetName() const; //获取名字
    const bool& GetSexuality() const;  //获取性别
    const QString& GetContact() const;  //获取联系方式

};



//住宿人员<-人
class resident:public people
{
protected:
    quint16 DormNumber; //宿舍号
    QString IdNumber;   //身份证号
public:
    resident();
    resident(const QString na, const bool sex, const QString &contact,
             const quint16 dN, const QString id);

    /*属性值获取函数*/
    const QString& GetIdNumber() const;
    const quint16& GetDormNumber() const;

    /*属性设置函数*/
    void SetDormNumber(const quint16 dorm);
    void SetIdNumber(const QString &idnumber);

};


//学生<-住宿人员<-人
class student: public resident
{
protected:
    QString StudentId;  //学号
    quint16 XueYuan;  //学院编号，用类静态字符串Map下标访问
    quint16 BanJi;  //班级编号，用类静态字符串Map下标访问

public:
    static QStringList list_of_XueYuan;
    static QList<QStringList> lists_of_BanJi;
    static Init_of_Xueyuan_and_BanJi(); //初始化学生类静态数据，学院，班级（计划改为文件读取）

    student();
    student(const QString &na, const bool sex, const QString &contact,
            const quint16 dN, const QString &id,
            const QString &stuid,const quint16 &xueyuan, const quint16 &bj);

    /*属性值获取函数*/
    const QString& GetStudentId() const;
    const quint16& GetXueYuan() const;
    const quint16& GetBanJi() const;

    /*属性值设置函数*/
    void SetStudentId(const QString &stuid);
    void SetXueYuan(const quint16 xueyuan);
    void SetBanji(const quint16 banji);

    /*转化为字符串*/
    QString toString();
    QString toString_detail();

    //输入输出运算符重载;
    friend QDataStream &operator <<(QDataStream &out, const student &obj);
    friend QDataStream &operator >>(QDataStream &in, student &obj);

    //比较运算符重载
    friend bool operator <(student &a, student &b);
};


#endif // PEOPLE_H



