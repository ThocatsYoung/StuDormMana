#include "room.h"

//dorm 宿舍类

dorm::dorm()
{

}

dorm::dorm(quint16 DN, quint16 MN, quint16 NN, double wf, double ef):
    DormNumber(DN), MaxNumber(MN), NowNumber(NN),
    WaterFee(wf), ElecFee(ef){}


const quint16 &dorm::GetDormNumber()
{
    return DormNumber;
}

const quint16 &dorm::GetMaxNumber()
{
    return MaxNumber;
}

const quint16 &dorm::GetNowNumber()
{
    return NowNumber;
}

const double &dorm::GetWaterFee()
{
    return WaterFee;
}

const double &dorm::GetElecFee()
{
    return ElecFee;
}

void dorm::SetWaterFee(double fee)
{
    WaterFee = fee;
}

void dorm::SetElecFee(double fee)
{
    ElecFee = fee;
}


void dorm::add(student &stu)
{
    StuDorm.append(stu);
    NowNumber++;
}

void dorm::goAway(QLinkedList<student>::iterator stu)
{
    StuDorm.erase(stu);
    NowNumber--;
}

void dorm::moveTo(QLinkedList<student>::iterator stu, dorm &newdorm)
{
    newdorm.StuDorm.append(*stu);
    StuDorm.erase(stu);
}

QDataStream &operator <<(QDataStream &out, const dorm &dor)
{
    out << dor.DormNumber << dor.MaxNumber << dor.NowNumber
        << dor.WaterFee << dor.ElecFee << dor.StuDorm;
    return out;
}

QDataStream &operator >>(QDataStream &in, dorm &dor)
{
    in >> dor.DormNumber >> dor.MaxNumber >> dor.NowNumber
       >> dor.WaterFee >> dor.ElecFee >> dor.StuDorm;
    return in;
}
