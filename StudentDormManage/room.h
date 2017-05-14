#ifndef ROOM_H
#define ROOM_H

#include <QLinkedList>
#include <QString>
#include <QDateTime>
#include <people.h>
//取消基类room，直接编写将其派生类宿舍与活动室作为两个独立类编写
//dorm 可能会改为类模板
class dorm
{
    quint32 DormNumber; //宿舍号
    quint8 MaxNumber;   //最大允许居住人数
    quint8 NowNumber;   //现居人数
    double WaterFee;    //水费
    double ElecFee; //电费
    QLinkedList<student> StuDorm;   //居住学生链表
public:
    dorm(quint32 DN, quint8 MN, quint8 NN,
         double wf, double ef);

    /*属性获取函数*/
    quint32& GetDormNumber() const;
    quint8& GetMaxNumber() const;
    quint8& GetNowNumber() const;
    double& GetWaterFee() const;
    double& GetElecFee() const;

    /*水电费设置函数*/
    void setWaterFee(double fee = 0.0); //设置水费，默认设为0
    void setElecFee(double fee = 0.0);  //设置电费，默认设为0
    double PayWater(double pay);    //所欠水费减去pay
    double PayElec(double pay); //所欠电费减去pay

    //人员操作
    void add(student& stu);  //加人
    void goAway(QLinkedList<student>::iterator stu); //踢人
    void moveTo(QLinkedList<student>::iterator stu,
                dorm& newdorm);    //移动学生到其他宿舍

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const dorm &dor);
    friend QDataStream &operator >>(QDataStream &in, dorm &dor);
};

#endif // ROOM_H
