#ifndef ROOM_H
#define ROOM_H

#include <QList>
#include <QString>
#include <QDateTime>
#include <people.h>
#include <QDataStream>
//取消基类room，直接编写将其派生类宿舍与活动室作为两个独立类编写
//dorm 可能会改为类模板
class dorm
{
private:
    quint16 DormNumber; //宿舍号
    quint16 MaxNumber;   //最大允许居住人数
    quint16 NowNumber;   //现居人数
    double WaterFee;    //水费
    double ElecFee; //电费
public:
    QList<student> StuDorm;   //居住学生链表
    dorm();
    dorm(quint16 DN, quint16 MN = 4, quint16 NN = 0,
         double wf = 0.0, double ef = 0.0);

    /*属性获取函数*/
    const quint16& GetDormNumber() const;
    const quint16& GetMaxNumber() const;
    const quint16& GetNowNumber() const;
    const double& GetWaterFee() const;
    const double& GetElecFee() const;

    /*水电费设置函数*/
    void SetWaterFee(double fee = 0.0); //设置水费，默认设为0
    void SetElecFee(double fee = 0.0);  //设置电费，默认设为0


    //人员操作
    void add(student& stu);  //加人
    void goAway(QList<student>::iterator stu); //踢人
    void moveTo(QList<student>::iterator stu,
                dorm& newdorm);    //移动学生到其他宿舍

    //输入输出运算符重载
    friend QDataStream &operator <<(QDataStream &out, const dorm &dor);
    friend QDataStream &operator >>(QDataStream &in, dorm &dor);

    //比较运算符重载
    friend bool operator <(dorm &a,dorm &b);
};

#endif // ROOM_H

