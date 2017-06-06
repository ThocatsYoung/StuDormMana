#include "dorm_repair.h"

dorm_repair::dorm_repair()
{

}

dorm_repair::dorm_repair(QString Dormnumber, QString Repair_case, QDate Report_Date):
    dormnumber(Dormnumber), repair_case(Repair_case), report_date(Report_Date)
{

}

QDataStream &operator << (QDataStream &out, const dorm_repair &Dorm_repair)
{
    out << Dorm_repair.dormnumber << Dorm_repair.repair_case
        << Dorm_repair.report_date;
    return out;
}

QDataStream &operator >> (QDataStream &in, dorm_repair &Dorm_repair)
{
    in >>Dorm_repair.dormnumber >> Dorm_repair.repair_case
            >> Dorm_repair.report_date;
    return in;
}

repair_record::repair_record()
{

}

repair_record::repair_record(QString Dormnumber, QString Repair_case, QDate Report_date, QDate Finish_date):
   dorm_repair(Dormnumber, Repair_case, Report_date), finish_date(Finish_date)
{

}

QDataStream &operator << (QDataStream &out, const repair_record &Repair_record)
{
    out << Repair_record.dormnumber << Repair_record.repair_case << Repair_record.report_date
        << Repair_record.finish_date;
    return out;
}

QDataStream &operator >> (QDataStream &in, repair_record &Repair_record)
{
    in >> Repair_record.dormnumber >> Repair_record.repair_case >> Repair_record.report_date
            >>Repair_record.finish_date;
    return in;
}
