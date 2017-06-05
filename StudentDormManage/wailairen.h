#ifndef WAILAIREN_H
#define WAILAIREN_H


#include <QDateTime>
#include <QString>
#include <QDataStream>


//外来人员记录类
class outsider
{
protected:
    QString Name;    //姓名
    QString Contact;//联系方式
    QDateTime ComeTime; //来访时间
    QString IdNumber;   //身份证号
    quint16 m_sex;//性别
public:
    outsider();
    outsider(const QString &na, const quint16 msex,const QString idnumber, const QString &contact,
             const QDateTime &cometime);

    /*属性值获取函数*/
    const QString& GetName() const; //获取名字
    const QString& GetContact() const;  //获取联系方式
    const QDateTime& GetComeTime() const;//获得来访时间
    const QString& GetIdNumber() const;//获取ID
    static QStringList sex_things;//性别
    const quint16& get_sex() const;//获取性别

    /*属性设置函数*/
    void SetName(const QString &NewName);   //设置名字
    void SetContact(const QString &NewContact); //设置联系方式
    void SetComeTime(const QDateTime &cometime);//设置来访时间
    void SetIdNumber(const QString &idnumber);//设置ID
    void Setmsex(const quint16 &msex);//设置性别
    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const outsider &obj);
    friend QDataStream &operator >>(QDataStream &in, outsider &obj);
};

#endif // WAILAIREN_H
