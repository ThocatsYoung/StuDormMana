#ifndef FORMFOROUTSIDERCOME_H
#define FORMFOROUTSIDERCOME_H

#include <QWidget>

namespace Ui {
class FormForOutsiderCome;
}

class FormForOutsiderCome : public QWidget
{
    Q_OBJECT

public:
    explicit FormForOutsiderCome(QWidget *parent = 0);
    ~FormForOutsiderCome();

private:
    Ui::FormForOutsiderCome *ui;
};

#endif // FORMFOROUTSIDERCOME_H
