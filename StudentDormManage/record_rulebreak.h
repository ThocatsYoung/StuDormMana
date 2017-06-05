#ifndef RECORD_RULEBREAK_H
#define RECORD_RULEBREAK_H

#include <QDate>
#include <QDataStream>

//违纪记录类
class record_rulebreak
{
private:
    quint16 dorm_number;    //违纪宿舍号
    quint16 breaked_rule;   //违纪编号
    QDate date; //日期
public:
    record_rulebreak();
    record_rulebreak(quint16 a_dorm_number, quint16 a_breaked_rule,
                     QDate a_date = QDate::currentDate());
    static QStringList break_rule_things;

    //获取属性值
    const quint16 get_dorm_number() const;
    const quint16 get_breaked_rule() const;
    const QDate get_date() const;

    QString toString() const;

    //重载运算符
    friend QDataStream& operator <<(QDataStream& out, const record_rulebreak &record);
    friend QDataStream& operator >>(QDataStream& in, record_rulebreak &record);
};

#endif // RECORD_RULEBREAK_H
