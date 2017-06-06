#ifndef GOOD_RECORD_H
#define GOOD_RECORD_H

#include <QGroupBox>

namespace Ui {
class good_record;
}

class good_record : public QGroupBox
{
    Q_OBJECT

public:
    explicit good_record(QWidget *parent = 0);
    ~good_record();

private:
    Ui::good_record *ui;
};

#endif // GOOD_RECORD_H
