#include "record_rulebreak.h"

QStringList record_rulebreak::break_rule_things =
{"违反宿舍作息制度", "存放违禁物品", "破坏宿舍设施"};



record_rulebreak::record_rulebreak()
{

}

record_rulebreak::record_rulebreak(quint16 a_dorm_number, quint16 a_breaked_rule, QDate a_date):
    dorm_number(a_dorm_number), breaked_rule(a_breaked_rule), date(a_date)
{

}

const quint16 record_rulebreak::get_dorm_number() const
{
    return dorm_number;
}

const quint16 record_rulebreak::get_breaked_rule() const
{
    return breaked_rule;
}

const QDate record_rulebreak::get_date() const
{
    return date;
}

QDataStream &operator <<(QDataStream &out, const record_rulebreak &record)
{
    out << record.dorm_number << record.breaked_rule << record.date;
    return out;
}

QDataStream &operator >>(QDataStream &in, record_rulebreak &record)
{
    in >> record.dorm_number >> record.breaked_rule >> record.date;
    return in;
}
