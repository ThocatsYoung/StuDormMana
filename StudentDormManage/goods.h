#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>
#include <QDataStream>
#include <QList>

//物品类
class goods
{
public:
    QString goodsname;
    qint32 total;
    qint32 nownumber;

    goods();
    goods(QString Goodsname, qint32 Total, qint32 Nownumber);

    friend QDataStream &operator << (QDataStream &out, const goods &Goods);
    friend QDataStream &operator >> (QDataStream &in, goods &Goods);

};

//记录类
class goods_record
{
public:
    QString goodsname;
    QString manname;
    QString phonenumber;
    qint32 usenumber;
    QDate borrowdate;
    QDate backdate;


    goods_record();
    goods_record(QString Goodsname, QString Manname, QString Phonenumber, qint32 Usenumber, QDate Borrowdate, QDate Backdate);

    friend QDataStream &operator << (QDataStream &out, const goods_record &Record_goods);
    friend QDataStream &operator >> (QDataStream &in, goods_record &Record_goods);

};

#endif // GOODS_H
