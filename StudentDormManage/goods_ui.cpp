#include "goods_ui.h"
#include "ui_goods_ui.h"

goods_ui::goods_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::goods_ui)
{
    ui->setupUi(this);
}

goods_ui::~goods_ui()
{
    delete ui;
}
