#include "formforoutsidercome.h"
#include "ui_formforoutsidercome.h"

FormForOutsiderCome::FormForOutsiderCome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForOutsiderCome)
{
    ui->setupUi(this);
}

FormForOutsiderCome::~FormForOutsiderCome()
{
    delete ui;
}
