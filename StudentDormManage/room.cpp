#include "room.h"

//dorm 宿舍类

dorm::dorm(quint32 DN, quint8 MN, quint8 NN, double wf, double ef):
    DormNumber(DN), MaxNumber(MN), NowNumber(NM),
    WaterFee(wf), ElecFee(ef){}


quint32 &dorm::GetDormNumber() const
{
    return DormNumber;
}

quint8 &dorm::GetMaxNumber() const
{
    return MaxNumber;
}

quint8 &dorm::GetNowNumber() const
{
    return NowNumber;
}

double &dorm::GetWaterFee() const
{
    return WaterFee;
}

double &dorm::GetElecFee() const
{
    return ElecFee;
}

void dorm::setWaterFee(double fee = 0.0)
{
    WaterFee = fee;
}

void dorm::setElecFee(double fee = 0.0)
{
    ElecFee = fee;
}

double dorm::PayWater(double pay = 0.0)
{
        WaterFee -= pay;
    return WaterFee;
}

double dorm::PayElec(double pay)
{
        ElecFee -= pay;
        return ElecFee;
}

void dorm::add(student &stu)
{
    StuDorm.push_back(stu);
}

void dorm::goAway(QLinkedList<student>::iterator stu)
{
    StuDorm.erase(stu);
}

void dorm::moveTo(QLinkedList<student>::iterator stu, dorm &newdorm)
{
    newdorm.StuDorm.push_back(*stu);
    StuDorm.erase(stu);
}

QDataStream &dorm::operator <<(QDataStream &out, const dorm &dor)
{
    out << dor.DormNumber << dor.MaxNumber << dor.NowNumber
        << dor.WaterFee << dor.ElecFee << dor.StuDorm;
    return out;
}

QDataStream &dorm::operator >>(QDataStream &in, dorm &dor)
{
    in >> dor.DormNumber >> dor.MaxNumber >> dor.NowNumber
       >> dor.WaterFee >> dor.ElecFee >> dor.StuDorm;
    return in;
}
