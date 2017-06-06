#ifndef DORM_REPAIR_H
#define DORM_REPAIR_H


#include <QString>
#include <QDate>
#include <QList>
#include <QDataStream>


class dorm_repair
{
public:
    QString dormnumber;
    QString repair_case;
    QDate report_date;
public:
    dorm_repair();
    dorm_repair(QString Dormnumber, QString Repair_case, QDate Report_Date);

    friend QDataStream &operator << (QDataStream &out, const dorm_repair &Dorm_repair);
    friend QDataStream &operator >> (QDataStream &in, dorm_repair &Dorm_repair);
};


//repair_record
class repair_record: public dorm_repair
{
public:
    QDate finish_date;

public:
    repair_record();
    repair_record(QString Dormnumber, QString Repair_case, QDate Report_date, QDate Finish_date);

    friend QDataStream &operator << (QDataStream &out, const repair_record &Repair_record);
    friend QDataStream &operator >> (QDataStream &in, repair_record &Repair_record);
};

#endif // DORM_REPAIR_H
