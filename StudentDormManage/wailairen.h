#ifndef WAILAIREN_H
#define WAILAIREN_H


#include <QDateTime>
#include <QString>
#include <QDataStream>

class outsider
{
protected:
    QString Name;
    QString Contact;
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
    const QDateTime& GetComeTime() const;
    const QString& GetIdNumber() const;//_____________________________________我加了个函数
    static QStringList sex_things;
    const quint16& get_sex() const;

    /*属性设置函数*/
    void SetName(const QString &NewName);   //设置名字
    void SetContact(const QString &NewContact); //设置联系方式
    void SetComeTime(const QDateTime &cometime);
    void SetIdNumber(const QString &idnumber);//——————————————————————————
    void Setmsex(const quint16 &msex);
    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const outsider &obj);
    friend QDataStream &operator >>(QDataStream &in, outsider &obj);
};

#endif // WAILAIREN_H
