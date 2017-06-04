#ifndef OUTSCHOOL_H
#define OUTSCHOOL_H

#include "read_from_file.h"

#include <QString>
#include <QDateTime>

class outschool
{
protected:
    QString Name;
    QString IdNumber;
    QString Contact;
    QDateTime OutTime;
    quint16 DormNumber;


public:
    outschool();
    outschool(const QString &na,const quint16 &Dorm,const QString &ID,const QString &Co,const QDateTime &time);
    const QString& GetName() const; //获取名字
    const QString& GetContact() const;  //获取联系方式
    const QDateTime& GetOutTime() const;
    const QString& GetIdNumber() const;//
    const quint16& GetDormNumber() const;
    friend QDataStream &operator <<(QDataStream &out, const outschool &obj);
    friend QDataStream &operator >>(QDataStream &in, outschool &obj);
};

#endif // OUTSCHOOL_H
