#include "room.h"

//dorm 宿舍类

void dorm::setMaxNumber(const quint16 &value)
{
    MaxNumber = value;
}

dorm::dorm()
{
    
}

dorm::dorm(quint16 DN, quint16 MN, double wf, double ef):
    DormNumber(DN), MaxNumber(MN),
    WaterFee(wf), ElecFee(ef)
{

}


const quint16 dorm::GetDormNumber() const
{
    return DormNumber;
}

const quint16 dorm::GetMaxNumber() const
{
    return MaxNumber;
}

const quint16 dorm::GetNowNumber() const
{
    return StuDorm.count();
}

const double dorm::GetWaterFee() const
{
    return WaterFee;
}

const double dorm::GetElecFee() const
{
    return ElecFee;
}

QStringList dorm::toStringList()
{
    QStringList sl;

    sl.append(QString("%1").arg(this->GetMaxNumber()));
    sl.append(QString("%1").arg(this->GetNowNumber()));
    sl.append(QString("%1").arg(this->GetWaterFee()));
    sl.append(QString("%1").arg(this->GetElecFee()));
    //按顺序存储： 最大人数 现居人数 水费 电费

    return sl;
}

void dorm::SetWaterFee(double fee)
{
    WaterFee = fee;
}

void dorm::SetElecFee(double fee)
{
    ElecFee = fee;
}


void dorm::add(student stu)
{
    StuDorm.append(stu);
}

void dorm::goAway(int index)
{
    StuDorm.removeAt(index);
}

void dorm::moveTo(int index, dorm *newdorm)
{
    newdorm->add(this->StuDorm.at(index));
    StuDorm.removeAt(index);
}

bool operator <(const dorm &a,const dorm &b)
{
    return (a.GetDormNumber() < b.GetDormNumber());
}

QDataStream &operator <<(QDataStream &out, const dorm &dor)
{
    out << dor.DormNumber << dor.MaxNumber
        << dor.WaterFee << dor.ElecFee << dor.StuDorm;
    return out;
}

QDataStream &operator >>(QDataStream &in, dorm &dor)
{
    in >> dor.DormNumber >> dor.MaxNumber
       >> dor.WaterFee >> dor.ElecFee >> dor.StuDorm;
    return in;
}

