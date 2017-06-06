#include <goods.h>

//goods类函数
goods::goods()
{

}

goods::goods(QString Goodsname, qint32 Total, qint32 Nownumber):
    goodsname(Goodsname), total(Total), nownumber(Nownumber)
{

}

QDataStream &operator << (QDataStream &out, const goods &Goods)
{
    out << Goods.goodsname << Goods.total << Goods.nownumber;
    return out;

}

QDataStream &operator >> (QDataStream &in, goods &Goods)
{
    in >> Goods.goodsname >>Goods.total >> Goods.nownumber;
    return in;

}


//goods_record类函数
goods_record::goods_record()
{

}

goods_record::goods_record(QString Goodsname, QString Manname, QString Phonenumber,
                           qint32 Usenumber, QDate Borrowdate, QDate Backdate):
    goodsname(Goodsname), manname(Manname), phonenumber(Phonenumber),
    usenumber(Usenumber), borrowdate(Borrowdate), backdate(Backdate)
{

}

QDataStream &operator << (QDataStream &out, const goods_record &Record_goods)
{
    out << Record_goods.goodsname << Record_goods.manname << Record_goods.phonenumber
        << Record_goods.usenumber << Record_goods.borrowdate << Record_goods.backdate;
    return out;

}

QDataStream &operator >> (QDataStream &in, goods_record &Record_goods)
{
    in >> Record_goods.goodsname >> Record_goods.manname >> Record_goods.phonenumber
            >>Record_goods.usenumber >> Record_goods.borrowdate >>Record_goods.backdate;
    return in;
}
